//==========================================
//
//  ���C�g�̐���(light.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "light.h"

//==========================================
//  �}�N����`
//==========================================
#define NUM_LIGHT (3) //�J�����̐�

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
D3DLIGHT9 g_Light[NUM_LIGHT]; //���C�g���

//==========================================
//  ����������
//==========================================
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[�J���ϐ��錾
	D3DXVECTOR3 vecDir; //�ݒ�p�̕����x�N�g��

	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		//���C�g���̃N���A
		ZeroMemory(&g_Light[nCnt], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_Light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̕�����ݒ�
		switch (nCnt)
		{
		case 0:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			g_Light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			g_Light[nCnt].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			g_Light[nCnt].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir); //�x�N�g���̐��K��
		g_Light[nCnt].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &g_Light[nCnt]);

		//���C�g��L��������
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//==========================================
//  �I������
//==========================================
void UninitLight(void)
{

}

//==========================================
//  �X�V����
//==========================================
void UpdateLight(void)
{

}
