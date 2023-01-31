//==========================================================
//
//�f�o�b�O�\������ [debugproc.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_

//**********************************************************
//�X�C�b�`�񋓌^�̒�`
//**********************************************************
typedef enum
{
	DEBUGTYPE_OFF = 0,	//�Ώۋ@�\�����삵�Ă��Ȃ����
	DEBUGTYPE_ON,		//�Ώۋ@�\�����삵�Ă�����
	DEBUGTYPE_MAX
}DEBUGTYPE;

//**********************************************************
//�v���g�^�C�v�錾
//**********************************************************
void InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);
void PrintDebugProc(const char *fmt, ...);

#endif