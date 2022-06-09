//===================================================================
//
//2Dアクションゲーム制作(block.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_ 

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//=======================================================
//ブロックの構造体の定義
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;			//使用しているかどうか
}Block;

//=======================================================
//プロトタイプ宣言
//=======================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth, float fHeight);
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, float fWidth, float fHeight);//当たり判定用の関数
#endif