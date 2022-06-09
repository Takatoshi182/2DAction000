//===================================================================
//
//2D�A�N�V�����Q�[������(Howto.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "howto.h"
#include "input.h"
#include "main.h"
#include"sound.h"
#include "fade.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureHowto = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHowto = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//===================================================================
//�^�C�g����ʂ̏���������
//===================================================================
void InitHowto(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//taiki.jpg",
		&g_pTextureHowto);

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffHowto,
		NULL);

	VERTEX_2D *pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHowto->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHowto->Unlock();

	//���ʉ�
	PlaySound(SOUND_LABEL_FieldOn);
}

//===================================================================
//�^�C�g����ʂ̏I������
//===================================================================
void UninitHowto(void)
{
	//BGM��~
	StopSound();

	//�o�b�t�@�j��
	if (g_pVtxBuffHowto != NULL)
	{
		g_pVtxBuffHowto->Release();
		g_pVtxBuffHowto = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureHowto != NULL)
	{
		g_pTextureHowto->Release();
		g_pTextureHowto = NULL;
	}
}

//===================================================================
//�^�C�g����ʂ̍X�V����
//===================================================================
void UpdateHowto(void)
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//ENTERorSTART�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(MODE_GAME);
		}
	}
}

//===================================================================
//�^�C�g����ʂ̕`�揈��
//===================================================================
void DrawHowto(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHowto, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureHowto);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//�v���~�e�B�u�̎��
}