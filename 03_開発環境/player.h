//=======================================================
//
//2D�A�N�V�����Q�[������(Player.h)
//Author:�匴���r
//
//=======================================================
#ifndef _PLAYER_H_		//��d�K�[�h�C���N���[�h
#define _PLAYER_H_

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include"main.h"

//=======================================================
//�v���C���[�\����
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR2 tex;
	D3DXVECTOR3 move;
	int nCounterAnime;
	int nPatternAnime;
	int nDirectionMove;	//����(0:�E,1:��)
	bool bIsJumping;	//�W�����v��
	int  nGetJewel;		//�擾���Ă���A�C�e����
	int nGetObjectID;	//�A�C�e����ID
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Player;

//=======================================================
//�}�N����`
//=======================================================
#define PLAYER_HEIGHT	(50.0f)
#define PLAYER_WIDTH	(12.5f)

//=======================================================
//�v���g�^�C�v�錾
//=======================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif
