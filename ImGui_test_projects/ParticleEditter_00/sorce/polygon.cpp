//==========================================
//
//  �|���S���̔ėp����(polygon.cpp)
//  Author : Tommoya Kanazaki
//
//==========================================
#include "polygon.h"

//==========================================
//  3D�o�[�e�b�N�X�o�b�t�@�̐���
//==========================================
LPDIRECT3DVERTEXBUFFER9 Init_3D_Polygon(int nNum)
{
	//���[�J���ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * nNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL
	);

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPolygon = 0; nCntPolygon < nNum; nCntPolygon++)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�@���x�N�g���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		if (nNum != 1)
		{
			//���_�f�[�^�̃|�C���^��i�߂�
			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();

	return pVtxBuff;
}

//==========================================
//  2D�o�[�e�b�N�X�o�b�t�@�̐���
//==========================================
LPDIRECT3DVERTEXBUFFER9 Init_2D_Polygon(int nNum)
{
	//���[�J���ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * nNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL
	);

	//���_�o�b�t�@�̌Ăяo��
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPolygon = 0; nCntPolygon < nNum; nCntPolygon++)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�@���x�N�g���̐ݒ�
			pVtx[nCnt].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		if (nNum != 1)
		{
			//���_�f�[�^�̃|�C���^��i�߂�
			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();

	return pVtxBuff;
}

//==========================================
//  �I������
//==========================================
void UninitPolygon(LPDIRECT3DVERTEXBUFFER9 *pVtxBuff)
{
	//���_�o�b�t�@�̔j��
	if ((*pVtxBuff) != NULL)
	{
		(*pVtxBuff)->Release();
		(*pVtxBuff) = NULL;
	}
}
