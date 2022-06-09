//===================================================================
//
//2D�A�N�V�����Q�[������(Block.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "block.h"
#include "player.h"

//===================================================================
//�}�N����`
//===================================================================
#define MAX_BLOCK	(128)						//�u���b�N�̍ő吔

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureBlock = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Block g_Block[MAX_BLOCK];						//�u���b�N�̏��

//===================================================================
//�u���b�N�̏���������
//===================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//block005.jpg",
		&g_pTextureBlock);

	//�u���b�N�̏�񏉊���
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].fWidth = 0.0f;
		g_Block[nCntBlock].fHeight = 0.0f;
		g_Block[nCntBlock].bUse = false;
	}

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(8.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(8.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	//�u���b�N�o��
	SetBlock(D3DXVECTOR3(500.0f, 230.0f, 0.0f), 100.0f, 50.0f);
	SetBlock(D3DXVECTOR3(680.0f, 350.0f, 0.0f), 70.0f, 50.0f);
	SetBlock(D3DXVECTOR3(650.0f, 720.0f, 0.0f), 720.0f, 50.0f);
	SetBlock(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 100.0f, 50.0f);
	SetBlock(D3DXVECTOR3(680.0f, 670.0f, 0.0f), 50.0f, 50.0f);
	SetBlock(D3DXVECTOR3(450.0f, 510.0f, 0.0f), 50.0f, 50.0f);
}

//===================================================================
//�u���b�N�I������
//===================================================================
void UninitBlock(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//===================================================================
//�u���b�N�X�V����
//===================================================================
void UpdateBlock(void)
{
	
}
//===================================================================
//�u���b�N�`�揈��
//===================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X�̎擾
	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���Ƃ�
		 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntBlock * 4,							//�`�悷��摜�̍ŏ��̒��_�C���f�b�N�X
				2);										//�|���S����
		}
	}
}

//�u���b�N�̐ݒu����
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;
	int nCntBlock;

	//���_�o�b�t�@���b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{//�u���b�N���g���Ă��Ȃ�

			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].fWidth = fWidth;
			g_Block[nCntBlock].fHeight = fHeight;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);

			g_Block[nCntBlock].bUse = true;

			break;
		}
		pVtx += 4;	//�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffBlock->Unlock();
} 

bool CollisionBlock(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pPosOld,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight)
{
	bool bIsLanding = false;	//���n���Ă��邩�ۂ��B

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if ((g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight) >= pPosOld->y &&
				(g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight) < pPos->y &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPos->x - fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//�ォ��̓����蔻��
			{
				bIsLanding = true;	//���n���Ă���
				pPos->y = g_Block[nCntBlock].pos.y - fHeight;
				pMove->y = 0.0f;
			}

			else if ((g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight) <= pPosOld->y - fHeight / 2 &&
				(g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight) > pPos->y - fHeight / 2 &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPos->x - fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//������̓����蔻��
			{
				pPos->y = g_Block[nCntBlock].pos.y + fHeight;
				pMove->y = 0.0f;
			}
		}

		//���E����̓����蔻��
		if (pPosOld->y<g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight&&
			pPosOld->y>g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight)//�v���C���[�̑O���y�͈̔͂��u���b�N�ɂ߂荞��ł���
		{
			if ((g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPosOld->x - fWidth) &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//�E����̓����蔻��
			{
				pPos->x = g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth + fWidth;
				pMove->x = 0.0f;
			}

			else if ((g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPosOld->x + fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) > (pPos->x - fWidth))//������̓����蔻��
			{
				pPos->x = g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth - fWidth;
				pMove->x = 0.0f;
			}
		}
	}
	return bIsLanding;
}
