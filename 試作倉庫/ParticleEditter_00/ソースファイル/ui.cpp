//==========================================
//
//  UI表示の制御(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "ui.h"
#include "particle.h"

//==========================================
//  グローバル変数宣言
//==========================================
//エフェクト管理変数
ImVec4 g_clear_color; //発生するエフェクトの色
D3DXVECTOR3 g_move; //移動量
D3DXVECTOR3 g_angle; //発射基準角
D3DXVECTOR3 g_pos; //発生原点
D3DXVECTOR2 g_angle_; //拡散角
static int g_nNumFrame; //1フレーム間に発生するエフェクトの数
static int g_nLife; //エフェクトの寿命
static float g_Radius; //エフェクトの半径

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
	ImGui::StyleColorsDark();

	//プラットフォーム/レンダラーとバックエンドの設定
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//変数の初期化
	//エフェクト管理変数
	g_clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	g_move = D3DXVECTOR3(25.0f, 25.0f, 25.0f);
	g_angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_angle_ = D3DXVECTOR2(629.0f, 0.0f);
	g_nNumFrame = 25;
	g_nLife = 25;
	g_Radius = 25.0f;
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

	//エフェクトウィンドウの生成
	ImGui::Begin(u8"パーティクルツール");

	//発生原点

	//発生原点誤差

	//パーティクルライフ

	//エフェクトライフ

	//ループon/off

	//初期速度

	//初期速度誤差

	//初期サイズ

	//初期角度(ポリゴン)

	//初期回転速度(ポリゴン)

	//初期カラー

	//重力

	//当たり判定

	//形状
	/*
		選択式
		選択内容によって別ウィンドウを表示
		形状ごとのステータスを設定する
	*/
	
	//最終速度

	//最終サイズ

	//最終角度(ポリゴン)

	//最終回転速度(ポリゴン)

	//最終カラー

	//エフェクトウィンドウの終了
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
//  色情報の取得
//==========================================
D3DXCOLOR GetColorData()
{
	//ローカル変数
	D3DXCOLOR colorData;

	//値の変換
	colorData.r = g_clear_color.x;
	colorData.g = g_clear_color.y;
	colorData.b = g_clear_color.z;
	colorData.a = g_clear_color.w;

	//値を返す
	return colorData;
}

//==========================================
//  数情報の取得
//==========================================
int GetNumData()
{
	return g_nNumFrame;
}

//==========================================
//  寿命情報の取得
//==========================================
int GetLifeData()
{
	return g_nLife;
}

//==========================================
//  半径の取得
//==========================================
float GetRadiusData()
{
	return g_Radius;
}

//==========================================
//  移動量の取得
//==========================================
D3DXVECTOR3 GetMoveData()
{
	return g_move;
}

//==========================================
//  拡散角情報取得
//==========================================
D3DXVECTOR3 GetAngleData()
{
	//ローカル変数宣言
	D3DXVECTOR3 angle = D3DXVECTOR3
	(
		D3DXToRadian(g_angle.x),
		D3DXToRadian(g_angle.y),
		D3DXToRadian(g_angle.z)
	);

	return angle;
}

//==========================================
//  拡散角情報の取得
//==========================================
D3DXVECTOR2 GetAngle()
{
	//返り値の設定
	g_angle_.y = (g_angle_.x - 1.0f) * 0.5f;

	return g_angle_;
}

//==========================================
//  発生原点情報の取得
//==========================================
D3DXVECTOR3 GetPosData()
{
	return g_pos;
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
