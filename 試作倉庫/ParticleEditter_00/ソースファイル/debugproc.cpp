//==========================================================
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "debugproc.h"
#include <string.h>
#include <stdio.h>
//#include "input.h"

//**********************************************************
//�}�N����`
//**********************************************************
#define MAX_DEBUGSTRING	(2048)	//�f�o�b�O�\���̍ő啶����
#define MAX_FLOATNUM	(2)		//�����_�ȉ��̕\������

//**********************************************************
//�O���[�o���ϐ�
//**********************************************************
LPD3DXFONT g_pBAKA = NULL;	//�t�H���g�ւ̃|�C���^
char g_aStrDebug[MAX_DEBUGSTRING];	//�f�o�b�O�\���p�̕�����
bool g_bDispDebug = false;	//�f�o�b�O�\����ON/OFF

//**********************************************************
//�v���g�^�C�v�錾
//**********************************************************
//void SetManual(void);

//**********************************************************
//�f�o�b�OONOFF�\�����b�Z�[�W
//**********************************************************
const char *c_apOnOff[DEBUGTYPE_MAX] =
{
	"OFF",
	"ON",
};

//**********************************************************
//�f�o�b�OONOFF�\�����b�Z�[�W
//**********************************************************
//const char *c_apMode[MODE_MAX] =
//{
//	"�^�C�g��",
//	"�`���[�g���A��",
//	"�Q�[��",
//	"�����L���O",
//};

//==========================================================
//�f�o�b�O�\���̏���������
//==========================================================
void InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pBAKA);

	//�f�o�b�O�\�����̃N���A
	memset(&g_aStrDebug[0], NULL, sizeof(g_aStrDebug));

	//�����\���ݒ�
#if _DEBUG
	g_bDispDebug = true;
#else NDEBUG
	g_bDispDebug = false;
#endif
}

//==========================================================
//�f�o�b�O�\���̏I������
//==========================================================
void UninitDebugProc(void)
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (g_pBAKA != NULL)
	{
		g_pBAKA->Release();
		g_pBAKA = NULL;
	}
}

//==========================================================
//�f�o�b�O�\���̍X�V����
//==========================================================
void UpdateDebugProc(void)
{
	//��������ݒ�
	//SetManual();

	//if (GetKeyboardTrigger(DIK_F1) == true)
	//{//F1�L�[�������ꂽ�Ƃ�
	//	g_bDispDebug = g_bDispDebug ? false : true;
	//}
}

//==========================================================
//�f�o�b�O�\���̕`�揈��
//==========================================================
void DrawDebugProc(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (g_bDispDebug == true)
	{//�f�o�b�N���[�h���I���̎�
		//�e�L�X�g�̕`��
		g_pBAKA->DrawText(NULL, &g_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//�f�o�b�O�\�����̃N���A
	memset(&g_aStrDebug[0], NULL, sizeof(g_aStrDebug));
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
void PrintDebugProc(const char *fmt, ...)
{
	va_list args;
	char aString[MAX_DEBUGSTRING];
	char aSaveString[MAX_DEBUGSTRING];
	int nLength;
	int nStopLength;

	//������̑��
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//�m�F����������ꍇ
			p++;	//�m�F�����܂Ői�߂�

			switch (*p)
			{
			case 'd':	//����
				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 'f':	//����
				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);

				//�����_�ȉ��̕����ڂ܂Ŋm�F
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{//�����_���������ꍇ

						//�����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);
						
						//�����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						//������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

				break;
			case 'c':	//����
				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 's':	//������
				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			}

			nStopLength = (int)strlen(p) + 1;
			//���������̊m�F���������̕���������炷
			memmove(p + nLength - 2, p, nStopLength);

			p--;	//�|�C���^��%�܂Ŗ߂�

			//�ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	//�������A������
	strcat(&g_aStrDebug[0], &aString[0]);
	
}

//==========================================================
//�\������e�L�X�g�ݒ�
//==========================================================
//void SetManual(void)
//{
//	//�f�o�b�O�ύX��FPS
//	PrintDebugProc("�y�f�o�b�O�\���z�yF1�z�yFPS�z %d\n", GetFPS());
//	PrintDebugProc("�y���݂̉�ʁz[%s]\n", c_apMode[GetMode()]);
//}
