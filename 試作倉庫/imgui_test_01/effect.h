//==========================================
//
//  �G�t�F�N�g�̐���(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, float fGravity = 0.0f);
int GetEffectNum(void);

#endif
