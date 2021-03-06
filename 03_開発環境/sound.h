//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_bgm001 = 0,						// ゲーム
	SOUND_LABEL_title000,						// タイトル
	SOUND_LABEL_FieldOn,						//説明画面
	SOUND_LABEL_成功した時の嬉しい音,			// クリア
	SOUND_LABEL_ゲームのボタン音_2,				// BGM1
	SOUND_LABEL_キラーン！_2,					// お宝獲得音
	SOUND_LABEL_ジャンプ_2,						// ジャンプ音
	SOUND_LABEL_失敗,							//ゲームオーバー
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
