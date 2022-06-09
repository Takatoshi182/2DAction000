//=======================================================
//
//2Dアクションゲーム制作(main.h)
//Author:大原隆俊
//
//=======================================================
#ifndef _MAIN_H_						//このマクロ定義がされてなかったら
#define _MAIN_H_						//2重インクルード防止のマクロ定義

//===================================================================
//インクルードファイル
//===================================================================
#include<windows.h>
#include"d3dx9.h"						//描画処理に必要
#include"dinput.h"
#include"xaudio2.h"						//サウンド処理に必要

//=======================================================
//ライブラリリンク
//=======================================================
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)の各様ライブラリ
#pragma comment(lib,"dxguid.lib")	//Directコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")	//システム、時刻取得に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要

//=======================================================
//マクロ定義
//=======================================================
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対策用マクロ
#define CLASS_NAME		"WindowClass"		//ウィンドウクラス名
#define WINDOW_NAME		"洞窟危機一髪～あと10秒でこの洞窟崩れるってマジですか？～"
#define SCREEN_WIDTH	(1280)				//ウィンドウ幅
#define SCREEN_HEIGHT	(720)				//ウィンドウ高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=======================================================
//画面（モード）の種類
//=======================================================
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_HOWTO,		//操作方法画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//ゲーム成功画面
	MODE_FALSE,		//ゲーム失敗画面
	MODE_MAX
}MODE;

//=======================================================
//プロトタイプ宣言
//=======================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void NextMode(MODE mode);

//=======================================================
//頂点情報[2D]の構造体を定義
//=======================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//差表変換用係数（1.0固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

#endif