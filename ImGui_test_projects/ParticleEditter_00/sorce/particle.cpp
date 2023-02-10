//==========================================
//
//  �p�[�e�B�N������(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"
#include "effect.h"

//==========================================
//  �p�[�e�B�N���\���̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //�������_
	D3DXVECTOR3 posError; //�������_�덷
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 moveError; //�ړ��ʌ덷
	D3DXVECTOR3 acceleration; //�����x
	D3DXVECTOR3 accelerationError; //�����x�덷
	D3DXVECTOR3 size; //�|���S���T�C�Y
	D3DXVECTOR3 sizeError; //�|���S���T�C�Y�덷
	D3DXVECTOR3 magnification; //�g�嗦
	D3DXVECTOR3 magnificationError; //�g�嗦�덷
	D3DXVECTOR3 rot; //�p�x
	D3DXVECTOR3 rotError; //�p�x�덷
	D3DXVECTOR3 rotSpeed; //��]���x
	D3DXVECTOR3 rotSpeedError; //��]�p�x
	D3DXCOLOR colStart; //�����J���[
	D3DXCOLOR colStartError; //�����J���[�덷
	D3DXCOLOR colEnd; //�ŏI�J���[
	D3DXCOLOR colEndError; //�ŏI�J���[�덷
	int nLife; //�p�[�e�B�N���̎���
	int nNumEffect; //1F���̔�����
	float fGravity; //�d�͂̒l
	bool bLoop; //���[�v�̐؂�ւ�
	bool bCollision; //�����蔻��̐؂�ւ�
	DRAWMODE drawmode; //�h���[���[�h
	EFFECT effectinfo; //�G�t�F�N�g�f�[�^
}PARTICLE;

//==========================================