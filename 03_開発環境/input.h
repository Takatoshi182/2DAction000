//=======================================================
//
//2Dアクションゲーム制作(input.h)
//Author:大原隆俊
//
//=======================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//=======================================================
//プロトタイプ宣言
//=======================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
#endif
