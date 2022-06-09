//===================================================================
//
//2D�A�N�V�����Q�[������(block.h)
//Author:�匴���r
//
//===================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_ 

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"

//=======================================================
//�u���b�N�̍\���̂̒�`
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Block;

//=======================================================
//�v���g�^�C�v�錾
//=======================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth, float fHeight);
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, float fWidth, float fHeight);//�����蔻��p�̊֐�
#endif