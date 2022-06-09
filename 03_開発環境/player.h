//=======================================================
//
//2Dアクションゲーム制作(Player.h)
//Author:大原隆俊
//
//=======================================================
#ifndef _PLAYER_H_		//二重ガードインクルード
#define _PLAYER_H_

//===================================================================
//インクルードファイル
//===================================================================
#include"main.h"

//=======================================================
//プレイヤー構造体
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR2 tex;
	D3DXVECTOR3 move;
	int nCounterAnime;
	int nPatternAnime;
	int nDirectionMove;	//向き(0:右,1:左)
	bool bIsJumping;	//ジャンプ中
	int  nGetJewel;		//取得しているアイテム数
	int nGetObjectID;	//アイテムのID
	bool bUse;			//使用しているかどうか
}Player;

//=======================================================
//マクロ定義
//=======================================================
#define PLAYER_HEIGHT	(50.0f)
#define PLAYER_WIDTH	(12.5f)

//=======================================================
//プロトタイプ宣言
//=======================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif
