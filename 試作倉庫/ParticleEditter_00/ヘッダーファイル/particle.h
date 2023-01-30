//==========================================
//
//  �p�[�e�B�N������(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//==========================================
//  �p�[�e�B�N���\���̒�`
//==========================================
typedef struct
{	
	//���_
	D3DXVECTOR3 pos; //�������_
	D3DXVECTOR3 posError; //�������_�덷

	//���x
	D3DXVECTOR3 moveStart; //�������x
	D3DXVECTOR3 moveAcceleration; //�ŏI���x
	D3DXVECTOR3 moveError; //���x�덷

	//�T�C�Y
	D3DXVECTOR3 size; //�����T�C�Y
	D3DXVECTOR3 magnification; //�ŏI�T�C�Y

	//��]
	D3DXVECTOR3 rot; //�����p�x(�|���S��)
	D3DXVECTOR3 rotate; //������]���x(�|���S��)

	//�F
	D3DXCOLOR colorStart; //�����J���[
	D3DXCOLOR colorEnd; //�ŏI�J���[

	//����
	int nLife_P; //�p�[�e�B�N�����C�t
	int nLife_E; //�G�t�F�N�g���C�t

	//���̑�
	float fGravity; //�d��
	bool bLoop; //���[�von/off
	bool bCollision; //�����蔻��

	//�`��
	/*
	�I����
	�I����e�ɂ���ĕʃE�B���h�E��\��
	�`�󂲂Ƃ̃X�e�[�^�X��ݒ肷��
	*/

}ParticleData;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void SetParticle(void);

#endif
