//=======================================================
//
//2Dアクションゲーム制作(Player.cpp)
//Author:大原隆俊
//
//=======================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "object.h"
#include "sound.h"
#include "score.h"
//===================================================================
//マクロ定数
//===================================================================
#define PLAYER_SPEED	(4.5f)
#define PLAYER_COUNTER	(10)
#define PLAYER_JUMP	(-20.0f)

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_player;									//プレイヤー構造体

//===================================================================
//ポリゴンの初期化設定
//===================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//最初のポリゴン生成
	g_player.pos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);

	//ジュエル数の初期化
	g_player.nGetJewel = 0;

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//player003.png",
		&g_pTexturePlayer);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//1つ目の四角形(下が中心になるので注意)
	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, -50.0f + g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, -50.0f + g_player.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//===================================================================
//ポリゴンの終了処理
//===================================================================
void UninitPlayer(void)
{
	StopSound();

	//バッファ破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	//テクスチャ破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//===================================================================
//ポリゴンの更新処理
//===================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	//頂点情報のポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_A) == true)
	{//左移動
		g_player.nDirectionMove = 1;
		g_player.move.x += sinf(-D3DX_PI * 0.5f) *PLAYER_SPEED;
		g_player.move.y += cosf(-D3DX_PI * 0.5f) *PLAYER_SPEED;

		g_player.nCounterAnime++;		//カウンター加算

		if ((g_player.nCounterAnime % PLAYER_COUNTER) == 0)
		{//一定時間経過
			 //カウンター更新
			g_player.nCounterAnime = (g_player.nPatternAnime + 1) % 4;

			//パターンNo.更新
			g_player.nPatternAnime = (g_player.nPatternAnime + 1) % 4;

			//テクスチャ更新
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}

		pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
		pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
		pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//右移動
		g_player.nDirectionMove = 0;
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;

		g_player.nCounterAnime++;		//カウンター加算

		if ((g_player.nCounterAnime % PLAYER_COUNTER) == 0)
		{//一定時間経過
		 //カウンター更新
			g_player.nCounterAnime = (g_player.nPatternAnime + 1) % 4;

			//パターンNo.更新
			g_player.nPatternAnime = (g_player.nPatternAnime + 1) % 4;

			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}

	}

	//二段ジャンプ阻止
	if (g_player.pos.y == SCREEN_HEIGHT)
	{
		g_player.bIsJumping = false;
	}

	//ジャンプする
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACEキーを押す

		if (g_player.bIsJumping == false)
		{
			g_player.move.y = PLAYER_JUMP;
			g_player.bIsJumping = true;

			PlaySound(SOUND_LABEL_ジャンプ_2);

			//テクスチャ座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * g_player.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.25f + g_player.nPatternAnime*0.25f, (1.0f / 2) * (g_player.nDirectionMove + 1));
		}
	}

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	//重力加算
	g_player.move.y += 1.0f;

	//位置更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//着地してからジャンプする
	g_player.bIsJumping = !(CollisionBlock(&g_player.pos,
		&g_player.posOld,
		&g_player.move,
		PLAYER_WIDTH,
		PLAYER_HEIGHT));

	//オブジェクトに当たる
	Object* hitObject = (CollisionObject(&g_player.pos,
		PLAYER_WIDTH/4,
		PLAYER_HEIGHT/4));

	//当たった後の各判定
	if (hitObject != NULL)
	{
		if (hitObject->type == 0)
		{//ジュエルに当たる
			hitObject->bUse = false; 

			//ジュエル獲得数追加
			g_player.nGetJewel += 1;

			//サウンド
			PlaySound(SOUND_LABEL_キラーン！_2);
		}
		
		else if (hitObject->type == 1)
		{//炎に当たる
			NextMode(MODE_FALSE);
		}

		else if (hitObject->type == 2)
		{//ゴールに到着
			NextMode(MODE_RESULT);
		}
	}
	
	//ジャンプ中はアニメーション固定
	if (g_player.bIsJumping == true)
	{
		g_player.nPatternAnime = 0;
	}

	//移動量更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x)*0.5f;	//目的の値-現在の値*減衰係数

	//止まったらアニメーションを止まってるモーションにする
	if (g_player.move == 0)
	{
		if (g_player.nPatternAnime == 1 || g_player.nPatternAnime == 3)
		{
			g_player.nPatternAnime ; 
		}
	}

	if (g_player.pos.y >= SCREEN_HEIGHT)
	{//地面より下にいかない
		g_player.pos.y = SCREEN_HEIGHT;
		g_player.move.y = 0.0f;
	}

	//プレイヤーが端までいった
	if (g_player.pos.x + 50.0f < 0.0f)
	{
		g_player.pos.x = SCREEN_WIDTH + 50.0f;
	}

	else if (g_player.pos.x - 50.0f > SCREEN_WIDTH)
	{
		g_player.pos.x = -50.0f;
	}

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, -PLAYER_HEIGHT + g_player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, -PLAYER_HEIGHT + g_player.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + g_player.pos.x, g_player.pos.y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//===================================================================
//ポリゴンの描画処理
//===================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブの種類
}

Player* GetPlayer(void)
{//プレイヤーが当たったときを返す
	return &g_player;
}