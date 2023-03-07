//==========================================
//
//  �G�t�F�N�g�̏���(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "polygon.h"
#include "texture.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_EFFECT (2048) //�G�t�F�N�g�̍ő�l

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];

//==========================================
//  ����������
//==========================================
void InitEffect()
{
	//�ϐ��̏�����
	ZeroMemory(&g_aEffect[0], sizeof(EFFECT) * MAX_EFFECT);
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_aEffect[nCnt].nDrawmode = DRAWMODE_DEFAULT;
		g_aEffect[nCnt].nTexPass = TEXTURE_EFFECT_DEFAULT;
	}

	//�|���S���̏�����
	g_pVtxBuffEffect = Init_3D_Polygon(MAX_EFFECT);
}

//==========================================
//  �I������
//==========================================
void UninitEffect()
{
	//�|���S���̔j��
	UninitPolygon(&g_pVtxBuffEffect);
}

//==========================================
//  �X�V����
//==========================================
void UpdateEffect()
{
	//�G�t�F�N�g�̍X�V
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//�g�p/�s�g�p�̔���
		if (g_aEffect[nCnt].bUse)
		{
			//�ړ�
			g_aEffect[nCnt].pos += g_aEffect[nCnt].move;

			//�����̌���
			if (g_aEffect[nCnt].nLife <= 0)
			{
				//�s�g�p�ɐݒ�
				g_aEffect[nCnt].bUse = false;
			}
			g_aEffect[nCnt].nLife--;
		}
	}
}

//==========================================
//  �`�揈��
//==========================================
void DrawEffect()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView; //�r���[�}�g���b�N�X�擾�p

	//���C�e�B���O�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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
			//�A���t�@�u�����f�B���O��ݒ�
			switch (g_aEffect[nCnt].nDrawmode)
			{
			case DRAWMODE_ADD: //���Z����
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case DRAWMODE_SAD: //���Z����
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			default: //�Ȃ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}

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
			pDevice->SetTexture(0, GetTexture(g_aEffect[nCnt].nTexPass));

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
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

	}

	//���C�e�B���O��L��������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  �ݒ菈��
//==========================================
void SetEffect(EFFECT effectdata)
{
	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse == false)
		{
			//�G�t�F�N�g�f�[�^��ݒ肷��
			g_aEffect[nCnt] = effectdata;

			//���_���W��ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCnt].size.x, g_aEffect[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCnt].size.x, g_aEffect[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCnt].size.x, -g_aEffect[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCnt].size.x, -g_aEffect[nCnt].size.y, 0.0f);

			//���_�J���[��ݒ�
			for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
			{
				pVtx[nCntVtx].col = g_aEffect[nCnt].colorStart;
			}

			//�g�p�ݒ�
			g_aEffect[nCnt].bUse = true;

			break;
		}
		//���_�f�[�^��i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//==========================================
//  �G�t�F�N�g�̎g�p�����擾
//==========================================
int GetEffectNum()
{
	//���[�J���ϐ��錾
	int nNum = 0;

	//�g�p���̃J�E���g
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse)
		{
			nNum++;
		}
	}

	return nNum;
}
