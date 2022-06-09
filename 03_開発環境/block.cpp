//===================================================================
//
//2Dアクションゲーム制作(Block.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "block.h"
#include "player.h"

//===================================================================
//マクロ定義
//===================================================================
#define MAX_BLOCK	(128)						//ブロックの最大数

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureBlock = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//頂点バッファへのポインタ
Block g_Block[MAX_BLOCK];						//ブロックの情報

//===================================================================
//ブロックの初期化処理
//===================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスへのポインタ
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//block005.jpg",
		&g_pTextureBlock);

	//ブロックの情報初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].fWidth = 0.0f;
		g_Block[nCntBlock].fHeight = 0.0f;
		g_Block[nCntBlock].bUse = false;
	}

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(8.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(8.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つずつ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	//ブロック出す
	SetBlock(D3DXVECTOR3(500.0f, 230.0f, 0.0f), 100.0f, 50.0f);
	SetBlock(D3DXVECTOR3(680.0f, 350.0f, 0.0f), 70.0f, 50.0f);
	SetBlock(D3DXVECTOR3(650.0f, 720.0f, 0.0f), 720.0f, 50.0f);
	SetBlock(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 100.0f, 50.0f);
	SetBlock(D3DXVECTOR3(680.0f, 670.0f, 0.0f), 50.0f, 50.0f);
	SetBlock(D3DXVECTOR3(450.0f, 510.0f, 0.0f), 50.0f, 50.0f);
}

//===================================================================
//ブロック終了処理
//===================================================================
void UninitBlock(void)
{
	//バッファ破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//===================================================================
//ブロック更新処理
//===================================================================
void UpdateBlock(void)
{
	
}
//===================================================================
//ブロック描画処理
//===================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = GetDevice();		//デバイスの取得
	
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{//ブロックが使用されているとき
		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntBlock * 4,							//描画する画像の最初の頂点インデックス
				2);										//ポリゴン数
		}
	}
}

//ブロックの設置処理
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;
	int nCntBlock;

	//頂点バッファロック
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{//ブロックが使われていない

			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].fWidth = fWidth;
			g_Block[nCntBlock].fHeight = fHeight;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);

			g_Block[nCntBlock].bUse = true;

			break;
		}
		pVtx += 4;	//ポインタを4つ進める
	}
	//頂点バッファアンロック
	g_pVtxBuffBlock->Unlock();
} 

bool CollisionBlock(D3DXVECTOR3*pPos,
	D3DXVECTOR3*pPosOld,
	D3DXVECTOR3*pMove,
	float fWidth,
	float fHeight)
{
	bool bIsLanding = false;	//着地しているか否か。

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			if ((g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight) >= pPosOld->y &&
				(g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight) < pPos->y &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPos->x - fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//上からの当たり判定
			{
				bIsLanding = true;	//着地している
				pPos->y = g_Block[nCntBlock].pos.y - fHeight;
				pMove->y = 0.0f;
			}

			else if ((g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight) <= pPosOld->y - fHeight / 2 &&
				(g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight) > pPos->y - fHeight / 2 &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPos->x - fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//下からの当たり判定
			{
				pPos->y = g_Block[nCntBlock].pos.y + fHeight;
				pMove->y = 0.0f;
			}
		}

		//左右からの当たり判定
		if (pPosOld->y<g_Block[nCntBlock].pos.y + g_Block[nCntBlock].fHeight&&
			pPosOld->y>g_Block[nCntBlock].pos.y - g_Block[nCntBlock].fHeight)//プレイヤーの前回のyの範囲がブロックにめり込んでいる
		{
			if ((g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) > (pPosOld->x - fWidth) &&
				(g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth) < (pPos->x + fWidth))//右からの当たり判定
			{
				pPos->x = g_Block[nCntBlock].pos.x + g_Block[nCntBlock].fWidth + fWidth;
				pMove->x = 0.0f;
			}

			else if ((g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) < (pPosOld->x + fWidth) &&
				(g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth) > (pPos->x - fWidth))//左からの当たり判定
			{
				pPos->x = g_Block[nCntBlock].pos.x - g_Block[nCntBlock].fWidth - fWidth;
				pMove->x = 0.0f;
			}
		}
	}
	return bIsLanding;
}
