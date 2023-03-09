//==========================================
//
//  UI�\���̐���(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <string.h>
#include "ui.h"
#include "effect.h"
#include "particle.h"
#include "texture.h"

//==========================================
//  �e�N�X�`���ꗗ
//==========================================
const char *c_pTextureName[TEXTURE_MAX] =
{
	u8"�f�t�H���g", //�G�t�F�N�g�Ńf�t�H���g�Ɏg���e�N�X�`��
	u8"�l�p�`" //�G�t�F�N�g�Ɏg�p����l�p�̃e�N�X�`��
}; //�e�N�X�`����

//==========================================
//  �v���g�^�C�v�錾
//==========================================
void SetParticleWindowBase(void); //�p�[�e�B�N���E�B���h�E�x�[�X�̐���
void SetParticleWindowIndex(void); //�����ς݃p�[�e�B�N���𒼐ڒ�������E�B���h�E�̐���
void SetCameraWindow(void); //�J�����E�B���h�E�̐���
void SetDebugWindow(void); //�f�o�b�O�E�B���h�E�̐���

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
//�p�[�e�B�N���Ǘ��ϐ�
PARTICLE g_particle;
int g_ListItemCurrent;
bool g_bIndexWindow;

//�J�����Ǘ��ϐ�
D3DXVECTOR3 g_posV; //���_�ʒu
D3DXVECTOR3 g_posR; //�����_�ʒu

//==========================================
//  ����������
//==========================================
void InitUi(HWND hWnd)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ImGui���̐ݒ�
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//�g�p����t�H���g
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//�t�H���g�T�C�Y
	const float FontSize = 15.0f;
	
	//�����̐ݒ�
	ImGuiIO & io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�X�^�C���̐ݒ�
	ImGui::StyleColorsLight();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//�ϐ��̏�����
	ZeroMemory(&g_particle, sizeof(PARTICLE));
	g_particle.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_particle.colStart = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_particle.nLife = 10;
	g_particle.size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_particle.nEffectLife = 10;
	g_particle.nNumEffect = 10;
	g_particle.effectinfo.nTexPass = TEXTURE_EFFECT_DEFAULT;
	g_ListItemCurrent = 0;
	g_bIndexWindow = false;

	//�J�����Ǘ��ϐ�
	g_posV = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
	g_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//==========================================
//  �I������
//==========================================
void UninitUi()
{
	//ImGui���I��
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  �X�V����
//==========================================
void UpdateUi()
{
	//ImGui�̎��s
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//�p�[�e�B�N���E�B���h�E�x�[�X�̐ݒ�
	SetParticleWindowBase();

	//�J�����E�B���h�E�̐ݒ�
	SetCameraWindow();

	//�f�o�b�O�E�B���h�E�̐ݒ�
	SetDebugWindow();

	//�X�V�̏I��
	ImGui::EndFrame();
}

//==========================================
//  �`�揈��
//==========================================
void DrawUi()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���C�e�B���O���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�`����e
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//���C�e�B���O���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ���_�ʒu���̎擾
//==========================================
D3DXVECTOR3 GetPosV()
{
	return g_posV;
}

//==========================================
//  �����_���̎擾
//==========================================
D3DXVECTOR3 GetPosR()
{
	return g_posR;
}

//==========================================
//  �p�[�e�B�N����ݒ肷��E�B���h�E
//==========================================
void SetParticleWindowBase()
{
	//�p�[�e�B�N���E�B���h�E�̐���
	ImGui::Begin(u8"�p�[�e�B�N���c�[��");

	//�����ʒu�̐ݒ�
	ImGui::DragFloat3(u8"�����ʒu", g_particle.pos);

	//�ړ��ʂ̐ݒ�
	ImGui::DragFloat3(u8"�ړ���", g_particle.move);

	//�g�U�̐ݒ�
	ImGui::DragFloat3(u8"�g�U�p", g_particle.diffuse);

	//�T�C�Y�̐ݒ�
	ImGui::DragFloat3(u8"�T�C�Y", g_particle.size);

	//�����̐ݒ�
	ImGui::InputInt(u8"�p�[�e�B�N�������̐ݒ�", &g_particle.nLife);

	//�����̐ݒ�
	ImGui::InputInt(u8"�G�t�F�N�g�����̐ݒ�", &g_particle.nEffectLife);

	//�������̐ݒ�
	ImGui::InputInt(u8"�������̐ݒ�", &g_particle.nNumEffect);

	//�����J���[�̐ݒ�
	ImGui::ColorEdit4(u8"�����J���[�̐ݒ�", g_particle.colStart);

	//�e�N�X�`���̐ݒ�
	ImGui::Combo(u8"�e�N�X�`���̐ݒ�", &g_particle.effectinfo.nTexPass, c_pTextureName, TEXTURE_MAX, TEXTURE_MAX);

	//���[�v�̃I���I�t
	ImGui::Checkbox(u8"���[�v", &g_particle.bLoop);

	//�`�惂�[�h�̐ݒ�
	ImGui::RadioButton(u8"���Z����", &g_particle.nDrawmode, DRAWMODE_ADD); ImGui::SameLine();
	ImGui::RadioButton(u8"���Z����", &g_particle.nDrawmode, DRAWMODE_SAD); ImGui::SameLine();
	ImGui::RadioButton(u8"�����Ȃ�", &g_particle.nDrawmode, DRAWMODE_DEFAULT);

	//�p�[�e�B�N���𔭐�������
	if (ImGui::Button("SetParticle"))
	{
		SetParticle(g_particle);
	} ImGui::SameLine();

	//�C���f�b�N�X�w�蒲���E�B���h�E�̐���
	ImGui::Checkbox("Index", &g_bIndexWindow);
	if(g_bIndexWindow)
	{
		SetParticleWindowIndex();
	}

	//�p�[�e�B�N���E�B���h�E�̏I��
	ImGui::End();
}

//==========================================
//  �C���f�b�N�X�w�葀��
//==========================================
void SetParticleWindowIndex()
{
	//�p�[�e�B�N�������擾����
	PARTICLE *pPraticle = GetParticleData();

	//�w�蒲���E�B���h�E�̐���
	ImGui::Begin(u8"�C���f�b�N�X�w��Œ�������");

	//�S�p�[�e�B�N���̃c���[�𐶐�
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pPraticle++)
	{
		//�\���p������̐ݒ�
		char aString[64];
		sprintf(&aString[0], "Index [ %d ]", nCntParticle);

		if (ImGui::CollapsingHeader(&aString[0]))
		{
			if (pPraticle->bUse)
			{
				//�e�L�X�g�̕\��
				ImGui::Text(u8"Particle[ %d ]���", nCntParticle);

				//�����ʒu�̐ݒ�
				ImGui::DragFloat3(u8"�����ʒu", pPraticle->pos);

				//�ړ��ʂ̐ݒ�
				ImGui::DragFloat3(u8"�ړ���", pPraticle->move);

				//�g�U�̐ݒ�
				ImGui::DragFloat3(u8"�g�U�p", pPraticle->diffuse);

				//�T�C�Y�̐ݒ�
				ImGui::DragFloat3(u8"�T�C�Y", pPraticle->size);

				//�����̐ݒ�
				ImGui::InputInt(u8"�p�[�e�B�N�������̐ݒ�", &pPraticle->nLife);

				//�����̐ݒ�
				ImGui::InputInt(u8"�G�t�F�N�g�����̐ݒ�", &pPraticle->nEffectLife);

				//�������̐ݒ�
				ImGui::InputInt(u8"�������̐ݒ�", &pPraticle->nNumEffect);

				//�����J���[�̐ݒ�
				ImGui::ColorEdit4(u8"�����J���[�̐ݒ�", pPraticle->colStart);

				//�e�N�X�`���̐ݒ�
				ImGui::Combo(u8"�e�N�X�`���̐ݒ�", &pPraticle->effectinfo.nTexPass, c_pTextureName, TEXTURE_MAX, TEXTURE_MAX);

				//���[�v�̃I���I�t
				ImGui::Checkbox(u8"���[�v", &pPraticle->bLoop); ImGui::SameLine();

				//�p�[�e�B�N���̍폜
				if (ImGui::Button(u8"����"))
				{
					pPraticle->bLoop = false;
					pPraticle->bUse = false;
				}

				//�`�惂�[�h�̐ݒ�
				ImGui::RadioButton(u8"���Z����", &pPraticle->nDrawmode, DRAWMODE_ADD); ImGui::SameLine();
				ImGui::RadioButton(u8"���Z����", &pPraticle->nDrawmode, DRAWMODE_SAD); ImGui::SameLine();
				ImGui::RadioButton(u8"�����Ȃ�", &pPraticle->nDrawmode, DRAWMODE_DEFAULT);

			}
			else
			{
				//�s�g�p��Ԃ�\��
				ImGui::Text(u8"Particle[ %d ] = false", nCntParticle); ImGui::SameLine();
				//�p�[�e�B�N���𔭐�������
				if (ImGui::Button("SetParticle"))
				{
					SetParticle(*pPraticle);
				}
			}
		}
	}

	//�w�蒲���E�B���h�E�̏I��
	ImGui::End();
}

//==========================================
//  �J�����E�B���h�E�̐���
//==========================================
void SetCameraWindow()
{
	//�J�����E�B���h�E�̐���
	ImGui::Begin(u8"�J�����ʒu�̊Ǘ�");

	//���_�̑���
	ImGui::DragFloat3("posV", (float*)&g_posV);
	ImGui::DragFloat3("posR", (float*)&g_posR);

	//�J�����E�B���h�E�̏I��
	ImGui::End();
}

//==========================================
//  �f�o�b�O�E�B���h�E�̐���
//==========================================
void SetDebugWindow()
{
	//�f�o�b�O�E�B���h�E�̐���
	ImGui::Begin(u8"�f�o�b�O�\��");

	//�G�t�F�N�g�̎g�p����\��
	ImGui::Text("EffectNum = %d", GetEffectNum());

	//�p�[�e�B�N���̎g�p����\��
	ImGui::Text("ParticleNum = %d", GetParticleNum());

	//�f�o�b�O�E�B���h�E�̏I��
	ImGui::End();
}
