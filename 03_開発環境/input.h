//=======================================================
//
//2D�A�N�V�����Q�[������(input.h)
//Author:�匴���r
//
//=======================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//===================================================================
//�C���N���[�h�t�@�C��
//===================================================================
#include "main.h"

//=======================================================
//�v���g�^�C�v�錾
//=======================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
#endif
