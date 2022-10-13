//===================================================================
//
//2Dアクションゲーム制作(time.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "time.h"
#include "main.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファへのポインタ
int  g_nTime;										//タイマーの値
D3DXVECTOR3 g_posTime;								//タイマーの位置
int g_nCntTime;										//タイマーカウント

//===================================================================
//タイムの初期化処理
//===================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureTime);

	//位置の初期化
	g_posTime = D3DXVECTOR3(1175.0f, 105.0f, 0.0f);

	//値の初期化
	g_nTime = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4*TIME_NUM),	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3((g_posTime.x - TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y - TIME_HEIGHT / 2, 0.0f);//（xのpos）+ずれる量
		pVtx[1].pos = D3DXVECTOR3((g_posTime.x + TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y - TIME_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posTime.x - TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y + TIME_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posTime.x + TIME_WIDTH / 2) + nCntTime * TIME_WIDTH, g_posTime.y + TIME_HEIGHT / 2, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//===================================================================
//タイムの終了処理
//===================================================================
void UninitTime(void)
{
	//バッファ破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//===================================================================
//タイムの更新処理
//===================================================================
void UpdateTime(void)
{
	g_nCntTime++;

	if (g_nCntTime % 60 == 0)
	{
		AddTime(-1);	//（）←ひかれる数
	}

	if (g_nTime == 0)
	{
		//ゲーム画面に遷移
		SetMode(MODE_FALSE);
	}
}

//===================================================================
//タイムの描画処理
//===================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTime);

	//ポリゴン描画
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);	//プリミティブの種類
	}
}

//===================================================================
//タイムの加算処理
//===================================================================
void AddTime(int nValue)
{
	VERTEX_2D*pVtx;						//頂点情報のポインタ
	int aPosTexU[TIME_NUM];				//各桁の数字を格納
	g_nTime += nValue;

	aPosTexU[0] = g_nTime % 100 / 10;	//10の位
	aPosTexU[1] = g_nTime % 10 / 1;		//1の位

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//===================================================================
//タイムの設置処理
//===================================================================
void SetTime(int nTime)
{
	VERTEX_2D*pVtx;						//頂点情報のポインタ
	int aPosTexU[TIME_NUM];				//各桁の数字を格納
	g_nTime = nTime;

	aPosTexU[0] = g_nTime % 100 / 10;	//10の位
	aPosTexU[1] = g_nTime % 10 / 1;		//1の位

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 0.1f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 0.1f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCntTime] + 1), 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}