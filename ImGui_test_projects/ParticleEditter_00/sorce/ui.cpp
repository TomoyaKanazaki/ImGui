//==========================================
//
//  UI�\���̐���(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "effect.h"

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
//�G�t�F�N�g�Ǘ��ϐ�

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
	ImGuiIO& io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGui�X�^�C���̐ݒ�
	ImGui::StyleColorsLight();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//�ϐ��̏�����

	//�J�����Ǘ��ϐ�
	g_posV = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
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

	//�p�[�e�B�N���E�B���h�E�̐���
	ImGui::Begin(u8"�p�[�e�B�N���c�[��");

	//�p�[�e�B�N���E�B���h�E�̏I��
	ImGui::End();

	//�J�����E�B���h�E�̐���
	ImGui::Begin(u8"�J�����ʒu�̊Ǘ�");

	//���_�̑���
	ImGui::DragFloat3("posV", (float*)&g_posV);
	ImGui::DragFloat3("posR", (float*)&g_posR);

	//�G�t�F�N�g�E�B���h�E�̏I��
	ImGui::End();

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
