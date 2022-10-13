//===================================================================
//
//2Dアクションゲーム制作(score.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "score.h"
#include "main.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファへのポインタ
int  g_nScore;										//スコアの値
D3DXVECTOR3 g_posScore;								//スコアの位置
int g_nCntScore;									//スコアカウント

//===================================================================
//スコアの初期化処理
//===================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//number000.png",
		&g_pTextureScore);

	//位置の初期化
	g_posScore = D3DXVECTOR3(750.0f, 390.0f, 0.0f);

	//値の初期化
	g_nScore = 0;

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * SCORE_NUM),	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3((g_posScore.x - SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y - SCORE_HEIGHT / 2, 0.0f);//（xのpos）+ずれる量
		pVtx[1].pos = D3DXVECTOR3((g_posScore.x + SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y - SCORE_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posScore.x - SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y + SCORE_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posScore.x + SCORE_WIDTH / 2) + nCntScore * SCORE_WIDTH, g_posScore.y + SCORE_HEIGHT / 2, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//===================================================================
//スコアの終了処理
//===================================================================
void UninitScore(void)
{
	//バッファ破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//===================================================================
//スコアの更新処理
//===================================================================
void UpdateScore(void)
{
	
}

//===================================================================
//スコアの描画処理
//===================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureScore);

	//ポリゴン描画
	for (int nCntScore = 0; nCntScore < SCORE_NUM; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);	//プリミティブの種類
	}

}

//===================================================================
//スコアの加算処理
//===================================================================
void AddScore(int nValue)
{
	VERTEX_2D*pVtx;							//頂点情報のポインタ
	int aPosTexU[SCORE_NUM];				//各桁の数字を格納
	g_nScore += nValue;

	aPosTexU[0] = g_nScore % 10 / 1;		//1の位

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//===================================================================
//スコアの設置処理
//===================================================================
void SetScore(int nScore)
{
	VERTEX_2D*pVtx;							//頂点情報のポインタ
	int aPosTexU[SCORE_NUM];				//各桁の数字を格納
	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 10 / 1;		//1の位

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[0] + 1), 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//===================================================================
//スコアの情報取得処理
//===================================================================
 int GetScore(void)
{
	return g_nScore; 
}