//==========================================
//
//  UI表示の制御(ui.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//==========================================
//  プロトタイプ宣言
//==========================================
void InitUi(HWND hWnd);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
//パーティクル

//カメラ
D3DXVECTOR3 GetPosV(void);
D3DXVECTOR3 GetPosR(void);

#endif
