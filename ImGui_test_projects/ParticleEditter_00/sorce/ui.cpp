//==========================================
//
//  UI表示の制御(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "effect.h"

//==========================================
//  グローバル変数宣言
//==========================================
//エフェクト管理変数

//カメラ管理変数
D3DXVECTOR3 g_posV; //視点位置
D3DXVECTOR3 g_posR; //注視点位置

//==========================================
//  初期化処理
//==========================================
void InitUi(HWND hWnd)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ImGui環境の設定
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//使用するフォント
	const char* FontPath = "data/font/GenShinGothic-Bold.ttf";

	//フォントサイズ
	const float FontSize = 15.0f;
	
	//文字の設定
	ImGuiIO& io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGuiスタイルの設定
	ImGui::StyleColorsLight();

	//プラットフォーム/レンダラーとバックエンドの設定
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//変数の初期化

	//カメラ管理変数
	g_posV = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	g_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//==========================================
//  終了処理
//==========================================
void UninitUi()
{
	//ImGuiを終了
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//==========================================
//  更新処理
//==========================================
void UpdateUi()
{
	//ImGuiの実行
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//パーティクルウィンドウの生成
	ImGui::Begin(u8"パーティクルツール");

	//パーティクルウィンドウの終了
	ImGui::End();

	//カメラウィンドウの生成
	ImGui::Begin(u8"カメラ位置の管理");

	//視点の操作
	ImGui::DragFloat3("posV", (float*)&g_posV);
	ImGui::DragFloat3("posR", (float*)&g_posR);

	//エフェクトウィンドウの終了
	ImGui::End();

	//更新の終了
	ImGui::EndFrame();
}

//==========================================
//  描画処理
//==========================================
void DrawUi()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ライティングをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//描画内容
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	//ライティングをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  視点位置情報の取得
//==========================================
D3DXVECTOR3 GetPosV()
{
	return g_posV;
}

//==========================================
//  注視点情報の取得
//==========================================
D3DXVECTOR3 GetPosR()
{
	return g_posR;
}
