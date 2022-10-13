//===================================================================
//
//2D�A�N�V�����Q�[������(time.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "time.h"
#include "main.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int  g_nTime;										//�^�C�}�[�̒l
D3DXVECTOR3 g_posTime;								//�^�C�}�[�̈ʒu
int g_nCntTime;										//�^�C�}�[�J�E���g

//===================================================================
//�^�C���̏���������
//===================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureTime);

	//�ʒu�̏�����
	g_posTime = D3DXVECTOR3(1175.0f, 105.0f, 0.0f);

	//�l�̏�����
	g_nTime = 0;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4*TIME_NUM),	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3((g_posTime.x - TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y - TIME_HEIGHT / 2, 0.0f);//�ix��pos�j+������
		pVtx[1].pos = D3DXVECTOR3((g_posTime.x + TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y - TIME_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posTime.x - TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y + TIME_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posTime.x + TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y + TIME_HEIGHT / 2, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//===================================================================
//�^�C���̏I������
//===================================================================
void UninitTime(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//===================================================================
//�^�C���̍X�V����
//===================================================================
void UpdateTime(void)
{
	g_nCntTime++;

	if (g_nCntTime % 60 == 0)
	{
		AddTime(-1);	//�i�j���Ђ���鐔
	}

	if (g_nTime == 0)
	{
		//�Q�[����ʂɑJ��
		SetMode(MODE_FALSE);
	}
}

//===================================================================
//�^�C���̕`�揈��
//===================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	//�|���S���`��
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);	//�v���~�e�B�u�̎��
	}
}

//===================================================================
//�^�C���̉��Z����
//===================================================================
void AddTime(int nValue)
{
	VERTEX_2D*pVtx;						//���_���̃|�C���^
	int aPosTexU[TIME_NUM];				//�e���̐������i�[
	g_nTime += nValue;

	aPosTexU[0] = g_nTime % 100 / 10;	//10�̈�
	aPosTexU[1] = g_nTime % 10 / 1;		//1�̈�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//===================================================================
//�^�C���̐ݒu����
//===================================================================
void SetTime(int nTime)
{
	VERTEX_2D*pVtx;						//���_���̃|�C���^
	int aPosTexU[TIME_NUM];				//�e���̐������i�[
	g_nTime = nTime;

	aPosTexU[0] = g_nTime % 100 / 10;	//10�̈�
	aPosTexU[1] = g_nTime % 10 / 1;		//1�̈�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 0.1f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 0.1f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}