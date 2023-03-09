//==========================================
//
//  �p�[�e�B�N������(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"

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
				if (g_aParticle[nCnt].diffuse.x != 0) //x
				{
					g_aParticle[nCnt].effectinfo.move.x = (float)(rand() % (int)(g_aParticle[nCnt].diffuse.x * 2.0f) - g_aParticle[nCnt].diffuse.x);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.x = 0;
				}

				if (g_aParticle[nCnt].diffuse.y != 0) //y
				{
					g_aParticle[nCnt].effectinfo.move.y = (float)(rand() % (int)(g_aParticle[nCnt].diffuse.y * 2.0f) - g_aParticle[nCnt].diffuse.y);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.y = 0;
				}

				if (g_aParticle[nCnt].diffuse.z != 0) //z
				{
					g_aParticle[nCnt].effectinfo.move.z = (float)(rand() % (int)(g_aParticle[nCnt].diffuse.z * 2.0f) - g_aParticle[nCnt].diffuse.z);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.z = 0;
				}

				//�G�t�F�N�g�̈ړ��ʂ�␳
				D3DXVec3Normalize(&g_aParticle[nCnt].effectinfo.move, &g_aParticle[nCnt].effectinfo.move);
				g_aParticle[nCnt].effectinfo.move.x *= g_aParticle[nCnt].move.x;
				g_aParticle[nCnt].effectinfo.move.y *= g_aParticle[nCnt].move.y;
				g_aParticle[nCnt].effectinfo.move.z *= g_aParticle[nCnt].move.z;

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
			if (g_aParticle[nCnt].nLife < 0)
			{
				g_aParticle[nCnt].nLife--;
			}
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
void SetParticle(PARTICLE particledata)
{
	//�p�[�e�B�N���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			//�擾��������ݒ�
			g_aParticle[nCnt] = particledata;

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

//==========================================
//  �p�[�e�B�N�����̎擾
//==========================================
PARTICLE *GetParticleData()
{
	return &g_aParticle[0];
}
