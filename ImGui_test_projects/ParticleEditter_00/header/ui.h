//==========================================
//
//  UI�\���̐���(ui.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitUi(HWND hWnd);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
//�p�[�e�B�N��

//�J����
D3DXVECTOR3 GetPosV(void);
D3DXVECTOR3 GetPosR(void);

#endif
