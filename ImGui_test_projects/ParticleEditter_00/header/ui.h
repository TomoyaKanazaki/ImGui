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
//エフェクト
D3DXCOLOR GetColorData(void);
int GetNumData(void);
int GetLifeData(void);
float GetRadiusData(void);
D3DXVECTOR3 GetMoveData(void);
D3DXVECTOR3 GetAngleData(void);
D3DXVECTOR3 GetPosData(void);
D3DXVECTOR2 GetAngle(void);
//カメラ
D3DXVECTOR3 GetPosV(void);
D3DXVECTOR3 GetPosR(void);

#endif
