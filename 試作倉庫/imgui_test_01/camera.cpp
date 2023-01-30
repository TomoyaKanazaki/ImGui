//==========================================
//
//  �J�����̐���(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "main.h"
#include "camera.h"
#include "ui.h"

//==========================================
//  �}�N����`
//==========================================
#define CAMERA_FOVY (54.0f) //����p

//==========================================
//  �O���[�o���ϐ�
//==========================================
Camera g_camera; //�J�����̏��

//==========================================
//�J�����̏���������
//==========================================
void InitCamera()
{
	//�e��ϐ��̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//==========================================
//  �J�����̏I������
//==========================================
void UninitCamera(void)
{

}

//==========================================
//  �J�����̍X�V����
//==========================================
void UpdateCamera(void)
{
	//�B�e�ʒu�̍X�V
	g_camera.posV = GetPosV();
	g_camera.posR = GetPosR();
}

//==========================================
//�J�����̐ݒ菈��
//==========================================
void SetCamera(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_FOVY),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
