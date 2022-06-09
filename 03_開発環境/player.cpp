//=======================================================
//
//2D�A�N�V�����Q�[������(Player.cpp)
//Author:�匴���r
//
//=======================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "object.h"
#include "sound.h"
#include "score.h"
//===================================================================
//�}�N���萔
//===================================================================
#define PLAYER_SPEED	(4.5f)
#define PLAYER_COUNTER	(10)
#define PLAYER_JUMP	(-20.0f)

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;									//�v���C���[�\����

//===================================================================
//�|���S���̏������ݒ�
//===================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ŏ��̃|���S������
	g_player.pos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);

	//�W���G�����̏�����
	g_player.nGetJewel = 0;

	//�e�N�X�`���ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player003.png",
		&g_pTexturePlayer);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//1�ڂ̎l�p�`(�������S�ɂȂ�̂Œ���)
	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, -50.0f + g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, -50.0f + g_player.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//===================================================================
//�|���S���̏I������
//===================================================================
void UninitPlayer(void)
{
	StopSound();

	//�o�b�t�@�j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//===================================================================
//�|���S���̍X�V����
//===================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_A) == true)
	{//���ړ�
		g_player.nDirectionMove = 1;
		g_player.move.x += sinf(-D3DX_PI * 0.5f) *PLAYER_SPEED;
		g_player.move.y += cosf(-D3DX_PI * 0.5f) *PLAYER_SPEED;

		g_player.nCounterAnime++;		//�J�E���^�[���Z

		if ((g_player.nCounterAnime % PLAYER_COUNTER) == 0)
		{//��莞�Ԍo��
			 //�J�E���^�[�X�V
			g_player.nCounterAnime = (g_player.nPatternAnime + 1) % 4;

			//�p�^�[��No.�X�V
			g_player.nPatternAnime = (g_player.nPatternAnime + 1) % 4;

			//�e�N�X�`���X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}

		pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
		pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
		pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//�E�ړ�
		g_player.nDirectionMove = 0;
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;

		g_player.nCounterAnime++;		//�J�E���^�[���Z

		if ((g_player.nCounterAnime % PLAYER_COUNTER) == 0)
		{//��莞�Ԍo��
		 //�J�E���^�[�X�V
			g_player.nCounterAnime = (g_player.nPatternAnime + 1) % 4;

			//�p�^�[��No.�X�V
			g_player.nPatternAnime = (g_player.nPatternAnime + 1) % 4;

			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}

	}

	//��i�W�����v�j�~
	if (g_player.pos.y == SCREEN_HEIGHT)
	{
		g_player.bIsJumping = false;
	}

	//�W�����v����
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACE�L�[������

		if (g_player.bIsJumping == false)
		{
			g_player.move.y = PLAYER_JUMP;
			g_player.bIsJumping = true;

			PlaySound(SOUND_LABEL_�W�����v_2);

			//�e�N�X�`�����W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}
	}

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	//�d�͉��Z
	g_player.move.y += 1.0f;

	//�ʒu�X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//���n���Ă���W�����v����
	g_player.bIsJumping = !(CollisionBlock(&g_player.pos,
		&g_player.posOld,
		&g_player.move,
		PLAYER_WIDTH,
		PLAYER_HEIGHT));

	//�I�u�W�F�N�g�ɓ�����
	Object* hitObject = (CollisionObject(&g_player.pos,
		PLAYER_WIDTH/4,
		PLAYER_HEIGHT/4));

	//����������̊e����
	if (hitObject != NULL)
	{
		if (hitObject->type == 0)
		{//�W���G���ɓ�����
			hitObject->bUse = false; 

			//�W���G���l�����ǉ�
			g_player.nGetJewel += 1;

			//�T�E���h
			PlaySound(SOUND_LABEL_�L���[���I_2);
		}
		
		else if (hitObject->type == 1)
		{//���ɓ�����
			NextMode(MODE_FALSE);
		}

		else if (hitObject->type == 2)
		{//�S�[���ɓ���
			NextMode(MODE_RESULT);
		}
	}
	
	//�W�����v���̓A�j���[�V�����Œ�
	if (g_player.bIsJumping == true)
	{
		g_player.nPatternAnime = 0;
	}

	//�ړ��ʍX�V�i�����j
	g_player.move.x += (0.0f - g_player.move.x)*0.5f;	//�ړI�̒l-���݂̒l*�����W��

	//�~�܂�����A�j���[�V�������~�܂��Ă郂�[�V�����ɂ���
	if (g_player.move == 0)
	{
		if (g_player.nPatternAnime == 1 || g_player.nPatternAnime == 3)
		{
			g_player.nPatternAnime ; 
		}
	}

	if (g_player.pos.y >= SCREEN_HEIGHT)
	{//�n�ʂ�艺�ɂ����Ȃ�
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.move.y = 0.0f;
	}

	//�v���C���[���[�܂ł�����
	if (g_player.pos.x + 50.0f < 0.0f)
	{
		g_player.pos.x = SCREEN_WIDTH + 50.0f;
	}

	else if (g_player.pos.x - 50.0f > SCREEN_WIDTH)
	{
		g_player.pos.x = -50.0f;
	}

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, -PLAYER_HEIGHT + g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, -PLAYER_HEIGHT + g_player.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//===================================================================
//�|���S���̕`�揈��
//===================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u�̎��
}

Player* GetPlayer(void)
{//�v���C���[�����������Ƃ���Ԃ�
	return &g_player;
}