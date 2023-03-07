//==========================================
//
//  �e�N�X�`���ݒ�p�t�@�C��(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"

//==========================================
//  �e�N�X�`���ꗗ
//==========================================
typedef enum
{
	TEXTURE_EFFECT_DEFAULT = 0, //�G�t�F�N�g�Ɏg�p����f�t�H���g�̂���
	TEXTURE_EFFECT_SQUARE, //�G�t�F�N�g�Ɏg�p����l�p�̃G�t�F�N�g
	TEXTURE_MAX
}TEXTURE_LABEL;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitTexture(void);
void UninitTexture(void);
LPDIRECT3DTEXTURE9 GetTexture(int TextureLabel);

#endif
