//==========================================
//
//  �e�N�X�`���̐���(texture.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "texture.h"
#include <string.h>

//==========================================
//  �}�N����`
//==========================================
#define TEXTURE_PASS "data\\TEXTURE\\" //�S�e�N�X�`���ɋ��ʂ���p�X
#define FORMAT_PNG ".png" //�e�N�X�`���̃t�@�C���`��
#define FORMAT_JPG ".jpg" //�e�N�X�`���̃t�@�C���`��

//==========================================
//  ����������(png)
//==========================================
LPDIRECT3DTEXTURE9 InitTexturePng(char aStr[MAX_STRING])
{
	//���[�J���ϐ��錾
	LPDIRECT3DTEXTURE9 pTexture;
	char aTexturePass[128] = TEXTURE_PASS;

	//�e�N�X�`���̃p�X��ݒ肷��
	strcat(&aTexturePass[0], &aStr[0]);
	strcat(&aTexturePass[0], FORMAT_PNG);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		&aTexturePass[0],
		&pTexture
	);

	//�ϐ���Ԃ�
	return pTexture;
}

//==========================================
//  ����������(jpg)
//==========================================
LPDIRECT3DTEXTURE9 InitTextureJpg(char aStr[MAX_STRING])
{
	//���[�J���ϐ��錾
	LPDIRECT3DTEXTURE9 pTexture;
	char aTexturePass[128] = TEXTURE_PASS;

	//�e�N�X�`���̃p�X��ݒ肷��
	strcat(&aTexturePass[0], &aStr[0]);
	strcat(&aTexturePass[0], FORMAT_JPG);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		&aTexturePass[0],
		&pTexture
	);

	//�ϐ���Ԃ�
	return pTexture;
}

//==========================================
//  �I������
//==========================================
void UninitTexture(LPDIRECT3DTEXTURE9 *pTexture, int nNum)
{
	for (int nCnt = 0; nCnt < nNum; nCnt++, pTexture++)
	{
		if ((*pTexture) != NULL)
		{
			(*pTexture)->Release();
			(*pTexture) = NULL;
		}
	}
}