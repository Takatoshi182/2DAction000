//===================================================================
//
//2D�A�N�V����(fade.cpp)
//Author:�匴���r
//
//===================================================================
//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include"fade.h"

//===================================================================
//�O���[�o���ϐ�
//===================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = NULL;					//���_�o�b�t�@�ւ̃|�C���^
static FADE g_fade;													//�t�F�[�h�̏��
static MODE g_modeNext;												//���̉��
static D3DXCOLOR g_colorFade;										//�t�F�[�h�i�|���S���j�̃J���[�ݒ�

//===================================================================
//�t�F�[�h�̏���������
//===================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	//�f���@�C�X�̎擾
	pDevice = GetDevice();

	g_fade = FADE_IN;

	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff, NULL);

	VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff->Unlock();

	//���[�h�̐ݒ�
	SetMode(g_modeNext);
}

//===================================================================
//�t�F�[�h�̏I������
//===================================================================
void UninitFade(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//===================================================================
//�t�F�[�h�̍X�V����
//===================================================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade.a -= 0.02f;
			if (g_colorFade <= 0.0f)
			{
				g_colorFade.a = 0.0f;

				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade.a += 0.02f;

			if (g_colorFade >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;			//�t�F�[�h�C�����

				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D * pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuff->Unlock();
	}

}

//===================================================================
//�t�F�[�h�̕`�揈��
//===================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//===================================================================
//�t�F�[�h�̐ݒ菈��
//===================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;

	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//===================================================================
//�t�F�[�h�̎擾����
//===================================================================
FADE GetFade(void)
{
	return g_fade;
}