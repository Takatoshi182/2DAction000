//===================================================================
//
//2D�A�N�V�����Q�[������(score.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "score.h"
#include "main.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int  g_nScore;										//�X�R�A�̒l
D3DXVECTOR3 g_posScore;								//�X�R�A�̈ʒu
int g_nCntScore;									//�X�R�A�J�E���g

//===================================================================
//�X�R�A�̏���������
//===================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureScore);

	//�ʒu�̏�����
	g_posScore = D3DXVECTOR3(750.0f, 390.0f, 0.0f);

	//�l�̏�����
	g_nScore = 0;

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * SCORE_NUM),	//�m�ۂ���o�b�t�@�̃T�C�Y 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3((g_posScore.x - SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y - SCORE_HEIGHT / 2, 0.0f);//�ix��pos�j+������
		pVtx[1].pos = D3DXVECTOR3((g_posScore.x + SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y - SCORE_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posScore.x - SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y + SCORE_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posScore.x + SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y + SCORE_HEIGHT / 2, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//===================================================================
//�X�R�A�̏I������
//===================================================================
void UninitScore(void)
{
	//�o�b�t�@�j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//�e�N�X�`���j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//===================================================================
//�X�R�A�̍X�V����
//===================================================================
void UpdateScore(void)
{
	
}

//===================================================================
//�X�R�A�̕`�揈��
//===================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	//�|���S���`��
	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);	//�v���~�e�B�u�̎��
	}

}

//===================================================================
//�X�R�A�̉��Z����
//===================================================================
void AddScore(int nValue)
{
	VERTEX_2D*pVtx;							//���_���̃|�C���^
	int aPosTexU[SCORE_NUM];				//�e���̐������i�[
	g_nScore += nValue;

	aPosTexU[0] = g_nScore % 10 / 1;		//1�̈�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//===================================================================
//�X�R�A�̐ݒu����
//===================================================================
void SetScore(int nScore)
{
	VERTEX_2D*pVtx;							//���_���̃|�C���^
	int aPosTexU[SCORE_NUM];				//�e���̐������i�[
	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 10 / 1;		//1�̈�

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//===================================================================
//�X�R�A�̏��擾����
//===================================================================
 int GetScore(void)
{
	return g_nScore; 
}