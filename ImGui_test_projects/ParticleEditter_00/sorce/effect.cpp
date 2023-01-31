//==========================================
//
//  �G�t�F�N�g�̐���(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "polygon.h"
#include "texture.h"
#include "ui.h"
#include "debugproc.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_EFFECT (65536) //�G�t�F�N�g�̍ő吔

//==========================================
//  �G�t�F�N�g�\���̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	int nLife;
	bool bUse;
	D3DXMATRIX mtxWorld;
}EFECT;

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL; //�o�b�t�@�ւ̃|�C���^
EFECT g_aEffect[MAX_EFFECT]; //�G�t�F�N�g�̏��
float g_aRadius[MAX_EFFECT]; //���a�̏����l
int g_aLife[MAX_EFFECT]; //�����̏����l
D3DXCOLOR g_aCol[MAX_EFFECT]; //�J���[�̏����l

//==========================================
//  ����������
//==========================================
void InitEffect(void)
{
	//����������
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_aEffect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCnt].nLife = 0;
		g_aEffect[nCnt].fRadius = 0.0f;
		g_aEffect[nCnt].bUse = false;
		g_aRadius[nCnt] = 0.0f;
		g_aLife[nCnt] = 0;
		g_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	g_pTextureEffect = InitTextureJpg("\\effect");

	//���_�o�b�t�@�̐���
	g_pVtxBuffEffect = InitPolygon(MAX_EFFECT);

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPolygon = 0; nCntPolygon < MAX_EFFECT; nCntPolygon++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�f�[�^�̃|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==========================================
//  �I������
//==========================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	UninitTexture(&g_pTextureEffect);

	//�|���S���̔j��
	UninitPolygon(&g_pVtxBuffEffect);
}

//==========================================
//  �X�V����
//==========================================
void UpdateEffect(void)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�X�V����
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse == true)
		{
			//�G�t�F�N�g���g�p����Ă���ꍇ

			//�G�t�F�N�g���k������
			g_aEffect[nCnt].fRadius -= (g_aRadius[nCnt] / (float)g_aLife[nCnt]);

			//�G�t�F�N�g�𔖂�����
			g_aEffect[nCnt].col.a -= (g_aCol[nCnt].a / (float)g_aLife[nCnt]);

			for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
			{
				//�����x�̍X�V
				pVtx[nCntVtx].col = g_aEffect[nCnt].col;
			}

			//���������炷
			g_aEffect[nCnt].nLife -= 1;

			//����0�̏ꍇ�e��s�g�p�ɂ���
			g_aEffect[nCnt].bUse = (g_aEffect[nCnt].nLife == 0) ? false : true;

			//�ړ��ʂ����Z����
			g_aEffect[nCnt].pos += g_aEffect[nCnt].move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCnt].fRadius, g_aEffect[nCnt].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCnt].fRadius, g_aEffect[nCnt].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCnt].fRadius, -g_aEffect[nCnt].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCnt].fRadius, -g_aEffect[nCnt].fRadius, 0.0f);
		}

		//���_�f�[�^�̃|�C���^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==========================================
//  �`�揈��
//==========================================
void DrawEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X�擾�p
	
	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCnt].mtxWorld);

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aEffect[nCnt].mtxWorld, NULL, &mtxView);

			//�l�̕␳
			g_aEffect[nCnt].mtxWorld._41 = 0.0f;
			g_aEffect[nCnt].mtxWorld._42 = 0.0f;
			g_aEffect[nCnt].mtxWorld._43 = 0.0f;

			//�ʒu�̔��f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCnt].pos.x, g_aEffect[nCnt].pos.y, g_aEffect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCnt].mtxWorld, &g_aEffect[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCnt].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�u�����f�B���O���̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  �ݒ菈��
//==========================================
void SetEffect(D3DXVECTOR3 pos, float fGravity)
{
	//�ݒ菈��
	for (int nCntNum = 0; nCntNum < GetNumData(); nCntNum++)
	{
		for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
		{
			if (g_aEffect[nCnt].bUse == false)
			{
				//�ʒu�̐ݒ�
				g_aEffect[nCnt].pos = GetPosData();

				//�ړ��ʂ̐ݒ�
				g_aEffect[nCnt].move = D3DXVECTOR3
				(
					(((float)(rand() % ((int)GetAngle().x) - ((int)GetAngle().y)) / 100.0f) + GetAngleData().x),
					(((float)(rand() % ((int)GetAngle().x) - ((int)GetAngle().y)) / 100.0f) + GetAngleData().y),
					(((float)(rand() % ((int)GetAngle().x) - ((int)GetAngle().y)) / 100.0f) + GetAngleData().z)
				);

				D3DXVec3Normalize(&g_aEffect[nCnt].move, &g_aEffect[nCnt].move);
				g_aEffect[nCnt].move.x *= GetMoveData().x;
				g_aEffect[nCnt].move.y *= GetMoveData().y;
				g_aEffect[nCnt].move.z *= GetMoveData().z;

				//�傫���̐ݒ�
				g_aEffect[nCnt].fRadius = GetRadiusData();
				g_aRadius[nCnt] = GetRadiusData();

				//�����x�̐ݒ�
				g_aEffect[nCnt].col = GetColorData();
				g_aCol[nCnt] = g_aEffect[nCnt].col;

				//�����̐ݒ�
				g_aEffect[nCnt].nLife = GetLifeData();
				g_aLife[nCnt] = GetLifeData();

				//�g�p/�s�g�p�̐ݒ�
				g_aEffect[nCnt].bUse = true;

				break;
			}
		}
	}
}

//==========================================
//  �g�p��Ԃ̎擾
//==========================================
int GetEffectNum()
{
	//���[�J���ϐ��錾
	int nCntEffect = 0;

	//�g�p���̃J�E���g
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse)
		{
			nCntEffect++;
		}
	}
	return nCntEffect;
}
