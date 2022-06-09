//===================================================================
//
//2Dアクション(fade.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include"fade.h"

//===================================================================
//グローバル変数
//===================================================================
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff = NULL;					//頂点バッファへのポインタ
static FADE g_fade;													//フェードの状態
static MODE g_modeNext;												//次の画面
static D3DXCOLOR g_colorFade;										//フェード（ポリゴン）のカラー設定

//===================================================================
//フェードの初期化処理
//===================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	//デヴァイスの取得
	pDevice = GetDevice();

	g_fade = FADE_IN;

	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff, NULL);

	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff->Unlock();

	//モードの設定
	SetMode(g_modeNext);
}

//===================================================================
//フェードの終了処理
//===================================================================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuff != NULL)
	{
		g_pVtxBuff->Release();
		g_pVtxBuff = NULL;
	}
}

//===================================================================
//フェードの更新処理
//===================================================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.02f;
			if (g_colorFade <= 0.0f)
			{
				g_colorFade.a = 0.0f;

				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.02f;

			if (g_colorFade >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;			//フェードイン状態

				//モードの設定
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D * pVtx;			//頂点情報へのポインタ

		//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
		g_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//頂点バッファをアンロックする
		g_pVtxBuff->Unlock();
	}

}

//===================================================================
//フェードの描画処理
//===================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//===================================================================
//フェードの設定処理
//===================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;

	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//===================================================================
//フェードの取得処理
//===================================================================
FADE GetFade(void)
{
	return g_fade;
}