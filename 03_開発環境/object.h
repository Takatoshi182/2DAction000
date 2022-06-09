//===================================================================
//
//2D�A�N�V�����Q�[������(object.h)
//Author:�匴���r
//
//===================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_ 

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"

//=======================================================
//�}�N���萔
//=======================================================
#define OBJECT_WIDTH	(50.0f)
#define OBJECT_HEIGHT	(50.0f)
#define GOAL_WIDTH		(50.0f)
#define GOAL_HEIGHT		(100.0f)
#define MAX_OBJECT		(128)	//�I�u�W�F�N�g�ő吔

//=======================================================
//�񋓌^�萔
//=======================================================
typedef enum
{
	OBJ_JEWEL =0,
	OBJ_FIRE,
	OBJ_GOAL,
	OBJ_MAX
}OBJ_TYPE;

//=======================================================
//�I�u�W�F�N�g�̍\���̂̒�`
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//��
	float fHeight;		//����
	OBJ_TYPE type;		//�I�u�W�F�N�g�̎��
	int nCounterFire;	//���̃J�E���^�[
	int nPatternFire;	//���̃p�^�[��
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Object;

//=======================================================
//�v���g�^�C�v�錾
//=======================================================
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(D3DXVECTOR3 pos, OBJ_TYPE object);
Object *CollisionObject(D3DXVECTOR3*pPos, float fWidth, float fHeight);//�����蔻��p�̊֐�
#endif