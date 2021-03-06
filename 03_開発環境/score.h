//===================================================================
//
//2Dアクションゲーム制作(score.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _SCORE_H_
#define _SCORE_H_ 

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//=======================================================
//スコア構造体
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex;
	int nScore;
}Score;

//=======================================================
//マクロ定義
//=======================================================
#define SCORE_HEIGHT	(120.0f)
#define SCORE_WIDTH	(90.0f)
#define SCORE_NUM	(1)

//=======================================================
//プロトタイプ宣言
//=======================================================
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
int GetScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
#endif