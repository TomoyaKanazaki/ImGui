//==========================================
//
//  �ėp�I�ȃ|���S���̐���(polygon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "main.h"

//==========================================
//  �v���g�^�C�v�錾
//==========================================
LPDIRECT3DVERTEXBUFFER9 InitPolygon(int nNum = 1); //�|���S�����̏��������s���֐�
void UninitPolygon(LPDIRECT3DVERTEXBUFFER9 *pVtxBuff); //�|���S�����̏I�����s���֐�
void DrawPolygon(void); //�|���S���̕`����s���֐�

#endif
