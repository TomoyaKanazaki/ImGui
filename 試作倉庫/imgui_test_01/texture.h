//==========================================
//
//  �e�N�X�`���̐���(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_STRING (64) //�����ɂȂ镶����̍ő�l

//==========================================
//  �v���g�^�C�v�錾
//==========================================
LPDIRECT3DTEXTURE9 InitTexturePng(char aStr[MAX_STRING]); //�e�N�X�`���̏��������s���֐�
LPDIRECT3DTEXTURE9 InitTextureJpg(char aStr[MAX_STRING]); //�e�N�X�`���̏��������s���֐�
void UninitTexture(LPDIRECT3DTEXTURE9 *pTexture,int nNum = 1); //�e�N�X�`���̔j�����s���֐�

#endif
