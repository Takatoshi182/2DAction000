//===================================================================
//
//2D�A�N�V�����Q�[������(object.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"
#include "object.h"
#include "player.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureObject[OBJ_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObject = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Object g_Object[MAX_OBJECT];						//�u���b�N�̏��

//===================================================================
//�u���b�N�̏�����
//===================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntObject;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//jewel.png",
		&g_pTextureObject[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//fire.png",
		&g_pTextureObject[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//goal1.png",
		&g_pTextureObject[2]);


	//�I�u�W�F�N�g�̏�񏉊���
	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].fWidth = 0.0f;
		g_Object[nCntObject].fHeight = 0.0f;
		g_Object[nCntObject].bUse = false;
	}

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffObject,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObject->Unlock();

	//�I�u�W�F�N�g�o��
	//�W���G��
	SetObject(D3DXVECTOR3(1085.0f, 650.0f, 0.0f), OBJ_TYPE(0));
	SetObject(D3DXVECTOR3(730.0f, 280.0f, 0.0f), OBJ_TYPE(0));
	SetObject(D3DXVECTOR3(200.0f, 330.0f, 0.0f), OBJ_TYPE(0));

	//��
	SetObject(D3DXVECTOR3(150.0f, 325.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(150.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(150.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(325.0f, 375.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(375.0f, 205.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 175.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 125.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 175.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 125.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(950.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(900.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(850.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(800.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(850.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 490.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 440.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 390.0f, 0.0f), OBJ_TYPE(1));

	//�S�[��
	SetObject(D3DXVECTOR3(1170.0f, 650.0f, 0.0f), OBJ_TYPE(2));
}

//===================================================================
//�I�u�W�F�N�g�I������
//===================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//�o�b�t�@�j��
		if (g_pVtxBuffObject != NULL)
		{
			g_pVtxBuffObject->Release();
			g_pVtxBuffObject = NULL;
		}
	}

	//�e�N�X�`���j��
	for (int nCntObject = 0; nCntObject < OBJ_MAX; nCntObject++)
	{
		if (g_pTextureObject[nCntObject] != NULL)
		{
			g_pTextureObject[nCntObject]->Release();
			g_pTextureObject[nCntObject] = NULL;
		}
	}
}

//===================================================================
//�I�u�W�F�N�g�X�V����
//===================================================================
void UpdateObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			if (g_Object[nCntObject].type == OBJ_FIRE)
			{
				VERTEX_2D *pVtx;	//���_���̃|�C���^
				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += 4 * nCntObject;

				g_Object[nCntObject].nCounterFire++;

				if ((g_Object[nCntObject].nCounterFire % 8) == 0)
				{//��莞�Ԍo��
				 //�p�^�[��No.�X�V
					g_Object[nCntObject].nPatternFire = (g_Object[nCntObject].nPatternFire + 1) % 4;

					//�e�N�X�`�����W�ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.0f + g_Object[nCntObject].nPatternFire * 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.25f + g_Object[nCntObject].nPatternFire * 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + g_Object[nCntObject].nPatternFire * 0.25f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + g_Object[nCntObject].nPatternFire * 0.25f, 1.0f);
				}
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffObject->Unlock();
			}
		}
	}
}

//===================================================================
//�I�u�W�F�N�g�`�揈��
//===================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObject, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{//�u���b�N���g�p����Ă���Ƃ�
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureObject[g_Object[nCntObject].type]);

		 //�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntObject * 4,							//�`�悷��摜�̍ŏ��̒��_�C���f�b�N�X
				2);										//�|���S����
		}
	}
}

//===================================================================
//�u���b�N�̐ݒu����
//===================================================================
void SetObject(D3DXVECTOR3 pos, OBJ_TYPE type)
{
	VERTEX_2D *pVtx;
	int nCntObject;

	//���_�o�b�t�@���b�N
	g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{//�I�u�W�F�N�g���g���Ă��Ȃ�
			g_Object[nCntObject].pos = pos;
			if (g_Object[nCntObject].type == 0 || 
				g_Object[nCntObject].type == 1)
			{//�W���G���Ɖ��̕��A�����ݒ�B
				g_Object[nCntObject].fWidth = OBJECT_WIDTH;
				g_Object[nCntObject].fHeight = OBJECT_HEIGHT;
				g_Object[nCntObject].nPatternFire = nCntObject % 4;		//���̃^�C�~���O���o���o���ɁB
			}

			else if (g_Object[nCntObject].type == 2)
			{//�S�[���̕��A�����ݒ�
				g_Object[nCntObject].fWidth = GOAL_WIDTH;
				g_Object[nCntObject].fHeight = GOAL_HEIGHT;
			}
			
			g_Object[nCntObject].type = type;

				//���_���W�̍X�V
				pVtx[1].pos = D3DXVECTOR3(pos.x + g_Object[nCntObject].fWidth / 2, pos.y - g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - g_Object[nCntObject].fWidth / 2, pos.y + g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(pos.x - g_Object[nCntObject].fWidth / 2, pos.y - g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + g_Object[nCntObject].fWidth / 2, pos.y + g_Object[nCntObject].fHeight / 2, 0.0f);
			
			if (g_Object[nCntObject].type == 1)
			{
				//�e�N�X�`���X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
			}
			
			else if (g_Object[nCntObject].type == 0 || g_Object[nCntObject].type == 2)
			{
				//�e�N�X�`���X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			
			g_Object[nCntObject].bUse = true;

			break;
		}
		pVtx += 4;	//�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffObject->Unlock();
}

//===================================================================
//�I�u�W�F�N�g�̓����蔻��
//===================================================================
Object *CollisionObject(D3DXVECTOR3*pPos, float fWidth, float fHeight)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			if ((g_Object[nCntObject].pos.y - g_Object[nCntObject].fHeight / 2) < pPos->y - fHeight / 2 &&
				(g_Object[nCntObject].pos.y + g_Object[nCntObject].fHeight / 2) > pPos->y - fHeight / 2 &&
				(g_Object[nCntObject].pos.x + g_Object[nCntObject].fWidth / 2) > pPos->x - fWidth / 2 &&
				(g_Object[nCntObject].pos.x - g_Object[nCntObject].fWidth / 2) < pPos->x + fWidth / 2)//�ォ��̓����蔻��
			{

				return &g_Object[nCntObject];//�v���C���[�ɓ����������Ƃ�Ԃ�

			}
		}
	}
	return NULL;
}



