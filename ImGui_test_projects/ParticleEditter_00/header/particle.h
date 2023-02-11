//==========================================
//
//  �p�[�e�B�N������(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"
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
	D3DXCOLOR colStart; //�����J���[
	D3DXCOLOR colStartError; //�����J���[�덷
	D3DXCOLOR colEnd; //�ŏI�J���[
	D3DXCOLOR colEndError; //�ŏI�J���[�덷
	int nLife; //�p�[�e�B�N���̎���
	int nNumEffect; //1F���̔�����
	float fGravity; //�d�͂̒l
	bool bUse; //�g�p�s�g�p�̐ݒ�
	bool bLoop; //���[�v�̐؂�ւ�
	bool bCollision; //�����蔻��̐؂�ւ�
	DRAWMODE drawmode; //�h���[���[�h
	EFFECT effectinfo; //�G�t�F�N�g�f�[�^
}PARTICLE;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
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
);

#endif