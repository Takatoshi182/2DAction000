//===================================================================
//
//2Dアクションゲーム制作(object.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "object.h"
#include "player.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureObject[OBJ_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObject = NULL;	//頂点バッファへのポインタ
Object g_Object[MAX_OBJECT];						//ブロックの情報

//===================================================================
//ブロックの初期化
//===================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntObject;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//jewel.png",
		&g_pTextureObject[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//fire.png",
		&g_pTextureObject[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//goal1.png",
		&g_pTextureObject[2]);


	//オブジェクトの情報初期化
	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nCntObject].fWidth = 0.0f;
		g_Object[nCntObject].fHeight = 0.0f;
		g_Object[nCntObject].bUse = false;
	}

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffObject,
		NULL);

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つずつ進める
	}


	//頂点バッファをアンロックする
	g_pVtxBuffObject->Unlock();

	//オブジェクト出す
	//ジュエル
	SetObject(D3DXVECTOR3(1085.0f, 650.0f, 0.0f), OBJ_TYPE(0));
	SetObject(D3DXVECTOR3(730.0f, 280.0f, 0.0f), OBJ_TYPE(0));
	SetObject(D3DXVECTOR3(200.0f, 330.0f, 0.0f), OBJ_TYPE(0));

	//炎
	SetObject(D3DXVECTOR3(150.0f, 325.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(150.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(150.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(325.0f, 375.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(375.0f, 205.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 175.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(680.0f, 125.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 275.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 225.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 175.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(630.0f, 125.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1040.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(950.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(900.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(850.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(800.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(850.0f, 340.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1130.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1210.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 640.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 590.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 540.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 490.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 440.0f, 0.0f), OBJ_TYPE(1));
	SetObject(D3DXVECTOR3(1250.0f, 390.0f, 0.0f), OBJ_TYPE(1));

	//ゴール
	SetObject(D3DXVECTOR3(1170.0f, 650.0f, 0.0f), OBJ_TYPE(2));
}

//===================================================================
//オブジェクト終了処理
//===================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		//バッファ破棄
		if (g_pVtxBuffObject != NULL)
		{
			g_pVtxBuffObject->Release();
			g_pVtxBuffObject = NULL;
		}
	}

	//テクスチャ破棄
	for (int nCntObject = 0; nCntObject < OBJ_MAX; nCntObject++)
	{
		if (g_pTextureObject[nCntObject] != NULL)
		{
			g_pTextureObject[nCntObject]->Release();
			g_pTextureObject[nCntObject] = NULL;
		}
	}
}

//===================================================================
//オブジェクト更新処理
//===================================================================
void UpdateObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			if (g_Object[nCntObject].type == OBJ_FIRE)
			{
				VERTEX_2D *pVtx;	//頂点情報のポインタ
				//頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += 4 * nCntObject;

				g_Object[nCntObject].nCounterFire++;

				if ((g_Object[nCntObject].nCounterFire % 8) == 0)
				{//一定時間経過
				 //パターンNo.更新
					g_Object[nCntObject].nPatternFire = (g_Object[nCntObject].nPatternFire + 1) % 4;

					//テクスチャ座標設定
					pVtx[0].tex = D3DXVECTOR2(0.0f + g_Object[nCntObject].nPatternFire * 0.25f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.25f + g_Object[nCntObject].nPatternFire * 0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + g_Object[nCntObject].nPatternFire * 0.25f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + g_Object[nCntObject].nPatternFire * 0.25f, 1.0f);
				}
				//頂点バッファをアンロックする
				g_pVtxBuffObject->Unlock();
			}
		}
	}
}

//===================================================================
//オブジェクト描画処理
//===================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	pDevice = GetDevice();		//デバイスの取得

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObject, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{//ブロックが使用されているとき
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureObject[g_Object[nCntObject].type]);

		 //ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				nCntObject * 4,							//描画する画像の最初の頂点インデックス
				2);										//ポリゴン数
		}
	}
}

//===================================================================
//ブロックの設置処理
//===================================================================
void SetObject(D3DXVECTOR3 pos, OBJ_TYPE type)
{
	VERTEX_2D *pVtx;
	int nCntObject;

	//頂点バッファロック
	g_pVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{//オブジェクトが使われていない
			g_Object[nCntObject].pos = pos;
			if (g_Object[nCntObject].type == 0 || 
				g_Object[nCntObject].type == 1)
			{//ジュエルと炎の幅、高さ設定。
				g_Object[nCntObject].fWidth = OBJECT_WIDTH;
				g_Object[nCntObject].fHeight = OBJECT_HEIGHT;
				g_Object[nCntObject].nPatternFire = nCntObject % 4;		//炎のタイミングをバラバラに。
			}

			else if (g_Object[nCntObject].type == 2)
			{//ゴールの幅、高さ設定
				g_Object[nCntObject].fWidth = GOAL_WIDTH;
				g_Object[nCntObject].fHeight = GOAL_HEIGHT;
			}
			
			g_Object[nCntObject].type = type;

				//頂点座標の更新
				pVtx[1].pos = D3DXVECTOR3(pos.x + g_Object[nCntObject].fWidth / 2, pos.y - g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - g_Object[nCntObject].fWidth / 2, pos.y + g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(pos.x - g_Object[nCntObject].fWidth / 2, pos.y - g_Object[nCntObject].fHeight / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + g_Object[nCntObject].fWidth / 2, pos.y + g_Object[nCntObject].fHeight / 2, 0.0f);
			
			if (g_Object[nCntObject].type == 1)
			{
				//テクスチャ更新
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
			}
			
			else if (g_Object[nCntObject].type == 0 || g_Object[nCntObject].type == 2)
			{
				//テクスチャ更新
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			
			g_Object[nCntObject].bUse = true;

			break;
		}
		pVtx += 4;	//ポインタを4つ進める
	}
	//頂点バッファアンロック
	g_pVtxBuffObject->Unlock();
}

//===================================================================
//オブジェクトの当たり判定
//===================================================================
Object *CollisionObject(D3DXVECTOR3*pPos, float fWidth, float fHeight)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == true)
		{
			if ((g_Object[nCntObject].pos.y - g_Object[nCntObject].fHeight / 2) < pPos->y - fHeight / 2 &&
				(g_Object[nCntObject].pos.y + g_Object[nCntObject].fHeight / 2) > pPos->y - fHeight / 2 &&
				(g_Object[nCntObject].pos.x + g_Object[nCntObject].fWidth / 2) > pPos->x - fWidth / 2 &&
				(g_Object[nCntObject].pos.x - g_Object[nCntObject].fWidth / 2) < pPos->x + fWidth / 2)//上からの当たり判定
			{

				return &g_Object[nCntObject];//プレイヤーに当たったことを返す

			}
		}
	}
	return NULL;
}



