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
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//�G�t�F�N�g�̏���ݒ�
			for (int nCntEffect = 0; nCntEffect < g_aParticle[nCnt].nNumEffect; nCntEffect++)
			{
				//�G�t�F�N�g�̔����ʒu��ݒ�
				g_aParticle[nCnt].effectinfo.pos = g_aParticle[nCnt].pos;

				//�G�t�F�N�g�̈ړ��ʂ�ݒ�
				if (g_aParticle[nCnt].move.x != 0) //x
				{
					g_aParticle[nCnt].effectinfo.move.x = (float)(rand() % (int)(g_aParticle[nCnt].move.x * 2.0f) - g_aParticle[nCnt].move.x);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.x = 0;
				}

				if (g_aParticle[nCnt].move.y != 0) //y
				{
					g_aParticle[nCnt].effectinfo.move.y = (float)(rand() % (int)(g_aParticle[nCnt].move.y * 2.0f) - g_aParticle[nCnt].move.y);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.y = 0;
				}

				if (g_aParticle[nCnt].move.z != 0) //z
				{
					g_aParticle[nCnt].effectinfo.move.z = (float)(rand() % (int)(g_aParticle[nCnt].move.z * 2.0f) - g_aParticle[nCnt].move.z);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.z = 0;
				}

				//�G�t�F�N�g�̑傫���̐ݒ�
				g_aParticle[nCnt].effectinfo.size = g_aParticle[nCnt].size;
	
				//�G�t�F�N�g�̏����J���[��ݒ�
				g_aParticle[nCnt].effectinfo.colorStart = g_aParticle[nCnt].colStart;
	
				//�G�t�F�N�g�̎�����ݒ�
				g_aParticle[nCnt].effectinfo.nLife = g_aParticle[nCnt].nEffectLife;
	
				//�`�惂�[�h�̐ݒ�
				g_aParticle[nCnt].effectinfo.nDrawmode = g_aParticle[nCnt].nDrawmode;

				//�G�t�F�N�g�̌Ăяo��
				SetEffect(g_aParticle[nCnt].effectinfo);
			}

			//�������Ȃ��Ȃ�����s�g�p�ɂ���
			if (g_aParticle[nCnt].nLife <= 0)
			{
				//���[�v�ݒ�̓K�p
				g_aParticle[nCnt].bUse = g_aParticle[nCnt].bLoop;
			}

			//����������
			g_aParticle[nCnt].nLife--;
		}
	}
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
	D3DXCOLOR colStart,
	int nLife,
	int nEffectLife,
	int nNumEffect,
	int nDrawmode,
	bool bLoop
)
{
	//�p�[�e�B�N���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			//���_�̐ݒ�
			g_aParticle[nCnt].pos = pos;

			//�ړ��ʂ̐ݒ�
			g_aParticle[nCnt].move = move;

			//�傫���̐ݒ�
			g_aParticle[nCnt].size = size;

			//�����J���[�̐ݒ�
			g_aParticle[nCnt].colStart = colStart;  

			//�p�[�e�B�N�������̐ݒ�
			g_aParticle[nCnt].nLife = nLife;

			//�G�t�F�N�g�����̐ݒ�
			g_aParticle[nCnt].nEffectLife = nEffectLife;

			//�G�t�F�N�g�������̐ݒ�
			g_aParticle[nCnt].nNumEffect = nNumEffect;

			//�`�惂�[�h�̐ݒ�
			g_aParticle[nCnt].nDrawmode = nDrawmode;

			//���[�v�̐ݒ�
			g_aParticle[nCnt].bLoop = bLoop;

			//�g�p��Ԃ�؂�ւ�
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}

//==========================================
//  �p�[�e�B�N���̎g�p�����擾
//==========================================
int GetParticleNum()
{
	//���[�J���ϐ��錾
	int nNum = 0;

	//�g�p���̃J�E���g
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			nNum++;
		}
	}

	return nNum;
}
