//==========================================
//
//  �G�t�F�N�g�̏���(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"

//==========================================
//  �}�N����`
//==========================================
#define MAX_TEXT (128) //�p�X�̍ő啶����

//==========================================
//  �񋓌^��`
//==========================================
typedef enum
{
	DRAWMODE_DEFAULT = 0, //�f�t�H���g�̕`��
	DRAWMODE_ADD, //���Z����
	DRAWMODE_SAD, //���Z����
	DRAWMODE_MAX
}DRAWMODE;

//==========================================
//  �\���̒�`
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //�������_
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 moveAcceleration; //�����x
	D3DXVECTOR3 size; //�|���S���T�C�Y
	D3DXVECTOR3 magnification; //�|���S���T�C�Y�g�嗦
	D3DXCOLOR colorStart; //�����J���[
	D3DXCOLOR colorEnd; //�ŏI�J���[
	int nLife; //����
	int nDrawmode; //�`�惂�[�h
	float fGravity; //�d��
	bool bCollision; //�����蔻��
	bool bUse; //�g�p/�s�g�p
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
}EFFECT;

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(EFFECT effectdata);
int GetEffectNum(void);

#endif
