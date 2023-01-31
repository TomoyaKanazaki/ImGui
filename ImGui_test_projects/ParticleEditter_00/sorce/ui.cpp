//==========================================
//
//  UI�\���̐���(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "particle.h"

//==========================================
//  �O���[�o���ϐ��錾
//==========================================
//�G�t�F�N�g�Ǘ��ϐ�
ImVec4 g_clear_color; //��������G�t�F�N�g�̐F
D3DXVECTOR3 g_move; //�ړ���
D3DXVECTOR3 g_angle; //���ˊ�p
D3DXVECTOR3 g_pos; //�������_
D3DXVECTOR2 g_angle_; //�g�U�p
static int g_nNumFrame; //1�t���[���Ԃɔ�������G�t�F�N�g�̐�
static int g_nLife; //�G�t�F�N�g�̎���
static float g_Radius; //�G�t�F�N�g�̔��a

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
	ImGui::StyleColorsDark();

	//�v���b�g�t�H�[��/�����_���[�ƃo�b�N�G���h�̐ݒ�
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//�ϐ��̏�����
	//�G�t�F�N�g�Ǘ��ϐ�
	g_clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	g_move = D3DXVECTOR3(25.0f, 25.0f, 25.0f);
	g_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_angle_ = D3DXVECTOR2(629.0f, 0.0f);
	g_nNumFrame = 25;
	g_nLife = 25;
	g_Radius = 25.0f;
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

	//�G�t�F�N�g�E�B���h�E�̐���
	ImGui::Begin(u8"�p�[�e�B�N���c�[��");

	//�������_

	//�������_�덷

	//�p�[�e�B�N�����C�t

	//�G�t�F�N�g���C�t

	//���[�von/off

	//�������x

	//�������x�덷

	//�����T�C�Y

	//�����p�x(�|���S��)

	//������]���x(�|���S��)

	//�����J���[

	//�d��

	//�����蔻��

	//�`��
	/*
		�I����
		�I����e�ɂ���ĕʃE�B���h�E��\��
		�`�󂲂Ƃ̃X�e�[�^�X��ݒ肷��
	*/
	
	//�ŏI���x

	//�ŏI�T�C�Y

	//�ŏI�p�x(�|���S��)

	//�ŏI��]���x(�|���S��)

	//�ŏI�J���[

	//�G�t�F�N�g�E�B���h�E�̏I��
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
//  �F���̎擾
//==========================================
D3DXCOLOR GetColorData()
{
	//���[�J���ϐ�
	D3DXCOLOR colorData;

	//�l�̕ϊ�
	colorData.r = g_clear_color.x;
	colorData.g = g_clear_color.y;
	colorData.b = g_clear_color.z;
	colorData.a = g_clear_color.w;

	//�l��Ԃ�
	return colorData;
}

//==========================================
//  �����̎擾
//==========================================
int GetNumData()
{
	return g_nNumFrame;
}

//==========================================
//  �������̎擾
//==========================================
int GetLifeData()
{
	return g_nLife;
}

//==========================================
//  ���a�̎擾
//==========================================
float GetRadiusData()
{
	return g_Radius;
}

//==========================================
//  �ړ��ʂ̎擾
//==========================================
D3DXVECTOR3 GetMoveData()
{
	return g_move;
}

//==========================================
//  �g�U�p���擾
//==========================================
D3DXVECTOR3 GetAngleData()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 angle = D3DXVECTOR3
	(
		D3DXToRadian(g_angle.x),
		D3DXToRadian(g_angle.y),
		D3DXToRadian(g_angle.z)
	);

	return angle;
}

//==========================================
//  �g�U�p���̎擾
//==========================================
D3DXVECTOR2 GetAngle()
{
	//�Ԃ�l�̐ݒ�
	g_angle_.y = (g_angle_.x - 1.0f) * 0.5f;

	return g_angle_;
}

//==========================================
//  �������_���̎擾
//==========================================
D3DXVECTOR3 GetPosData()
{
	return g_pos;
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
