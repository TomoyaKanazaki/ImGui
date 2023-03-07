//==========================================
//
//  �e�N�X�`���Ǘ��p�t�@�C��(texture.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "texture.h"

//==========================================
//  �e�N�X�`���t�@�C���ꗗ
//==========================================
const char *c_pTextureFilePass[TEXTURE_MAX] =
{
	"data/TEXTURE/effect_000.jpg" //�G�t�F�N�g�Ńf�t�H���g�Ɏg���e�N�X�`��
};

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 g_pTexture[TEXTURE_MAX] = {};

//==========================================
//  ����������
//==========================================
void InitTexture()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile
		(
			pDevice,
			c_pTextureFilePass[nCnt],
			&g_pTexture[nCnt]
		);
	}
}

//==========================================
//  �I������
//==========================================
void UninitTexture()
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++)
	{
		if (g_pTexture[nCnt] != NULL)
		{
			g_pTexture[nCnt]->Release();
			g_pTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  �e�N�X�`���̎擾����
//==========================================
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_LABEL TextureLabel)
{
	return g_pTexture[TextureLabel];
}
