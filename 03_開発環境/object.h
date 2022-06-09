//===================================================================
//
//2Dアクションゲーム制作(object.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_ 

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//=======================================================
//マクロ定数
//=======================================================
#define OBJECT_WIDTH	(50.0f)
#define OBJECT_HEIGHT	(50.0f)
#define GOAL_WIDTH		(50.0f)
#define GOAL_HEIGHT		(100.0f)
#define MAX_OBJECT		(128)	//オブジェクト最大数

//=======================================================
//列挙型定数
//=======================================================
typedef enum
{
	OBJ_JEWEL =0,
	OBJ_FIRE,
	OBJ_GOAL,
	OBJ_MAX
}OBJ_TYPE;

//=======================================================
//オブジェクトの構造体の定義
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//幅
	float fHeight;		//高さ
	OBJ_TYPE type;		//オブジェクトの種類
	int nCounterFire;	//炎のカウンター
	int nPatternFire;	//炎のパターン
	bool bUse;			//使用しているかどうか
}Object;

//=======================================================
//プロトタイプ宣言
//=======================================================
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(D3DXVECTOR3 pos, OBJ_TYPE object);
Object *CollisionObject(D3DXVECTOR3*pPos, float fWidth, float fHeight);//当たり判定用の関数
#endif