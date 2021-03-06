//===================================================================
//
//2Dアクションゲーム制作(false.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "false.h"
#include "input.h"
#include "main.h"
#include "sound.h"
#include "fade.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureFalse = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFalse = NULL;	//頂点バッファへのポインタ

//===================================================================
//失敗画面の初期化処理
//===================================================================
void InitFalse(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//false.png",
		&g_pTextureFalse);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffFalse,
		NULL);

	VERTEX_2D *pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFalse->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffFalse->Unlock();

	//BGM
	PlaySound(SOUND_LABEL_失敗);
}

//===================================================================
//失敗画面の終了処理
//===================================================================
void UninitFalse(void)
{
	StopSound();

	//バッファ破棄
	if (g_pVtxBuffFalse != NULL)
	{
		g_pVtxBuffFalse->Release();
		g_pVtxBuffFalse = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureFalse != NULL)
	{
		g_pTextureFalse->Release();
		g_pTextureFalse = NULL;
	}
}

//===================================================================
//失敗画面の更新処理
//===================================================================
void UpdateFalse(void)
{

	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//ENTERorSTARTが押されたかどうか
		if (GetKeyboardTrigger(DIK_SPACE) == true )
		{//失敗画面に遷移
			SetFade(MODE_TITLE);
		}

		else if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//ゲーム画面に遷移
			SetMode(MODE_GAME);
		}
	}
}

//===================================================================
//失敗画面の描画処理
//===================================================================
void DrawFalse(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFalse, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureFalse);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブの種類
}