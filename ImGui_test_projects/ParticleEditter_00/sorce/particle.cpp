//==========================================
//
//  �p�[�e�B�N������(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_PARTICLE (32) //�p�[�e�B�N���ő吔

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
PARTICLE g_aParticle[MAX_PARTICLE];

//==========================================
//  ����������
//==========================================
void InitParticle()
{
	//�ϐ��̏�����
	ZeroMemory(&g_aParticle[0], sizeof(PARTICLE) * MAX_PARTICLE);
	
	//�s�g�p��Ԃɏ���������
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].bUse = false;
	}
}

//==========================================
//  �I������
//==========================================
void UninitParticle()
{

}

//==========================================
//  �X�V����
//==========================================
void UpdateParticle()
{

}

//==========================================
//  �`�揈��
//==========================================
void DrawParticle()
{

}

//==========================================
//  �ݒ菈��
//==========================================
void SetParticle
(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 move,
	//D3DXVECTOR3 acceleration,
	D3DXVECTOR3 size,
	//D3DXVECTOR3 magnification,
	int nLife,
	int nNumEffect,
	bool bLoop
)
{
	//�p�[�e�B�N���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			//���_�̐ݒ�
			g_aParticle[nCnt].effectinfo.pos = pos;

			//�ړ��ʂ̐ݒ�
			g_aParticle[nCnt].effectinfo.move = move;

			//�傫���̐ݒ�
			g_aParticle[nCnt].effectinfo.size = size;

			//�����̐ݒ�
			g_aParticle[nCnt].nLife = nLife;

			//�g�p��Ԃ�؂�ւ�
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}
