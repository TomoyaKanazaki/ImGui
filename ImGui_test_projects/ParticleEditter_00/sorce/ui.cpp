//==========================================
//
//  UI表示の制御(ui.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <string.h>
#include "ui.h"
#include "effect.h"
#include "particle.h"
#include "texture.h"

//==========================================
//  テクスチャ一覧
//==========================================
const char *c_pTextureName[TEXTURE_MAX] =
{
	u8"デフォルト", //エフェクトでデフォルトに使うテクスチャ
	u8"四角形" //エフェクトに使用する四角のテクスチャ
}; //テクスチャ名

//==========================================
//  プロトタイプ宣言
//==========================================
void SetParticleWindowBase(void); //パーティクルウィンドウベースの生成
void SetParticleWindowIndex(void); //生成済みパーティクルを直接調整するウィンドウの生成
void SetCameraWindow(void); //カメラウィンドウの生成
void SetDebugWindow(void); //デバッグウィンドウの生成

//==========================================
//  グローバル変数宣言
//==========================================
//パーティクル管理変数
PARTICLE g_particle;
int g_ListItemCurrent;
bool g_bIndexWindow;

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
	ImGuiIO & io = ImGui::GetIO();

	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF(FontPath, FontSize, nullptr, io.Fonts->GetGlyphRangesJapanese());

	//ImGuiスタイルの設定
	ImGui::StyleColorsLight();

	//プラットフォーム/レンダラーとバックエンドの設定
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	//変数の初期化
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

	//カメラ管理変数
	g_posV = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
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

	//パーティクルウィンドウベースの設定
	SetParticleWindowBase();

	//カメラウィンドウの設定
	SetCameraWindow();

	//デバッグウィンドウの設定
	SetDebugWindow();

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

//==========================================
//  パーティクルを設定するウィンドウ
//==========================================
void SetParticleWindowBase()
{
	//パーティクルウィンドウの生成
	ImGui::Begin(u8"パーティクルツール");

	//発生位置の設定
	ImGui::DragFloat3(u8"発生位置", g_particle.pos);

	//移動量の設定
	ImGui::DragFloat3(u8"移動量", g_particle.move);

	//拡散の設定
	ImGui::DragFloat3(u8"拡散角", g_particle.diffuse);

	//サイズの設定
	ImGui::DragFloat3(u8"サイズ", g_particle.size);

	//寿命の設定
	ImGui::InputInt(u8"パーティクル寿命の設定", &g_particle.nLife);

	//寿命の設定
	ImGui::InputInt(u8"エフェクト寿命の設定", &g_particle.nEffectLife);

	//発生数の設定
	ImGui::InputInt(u8"発生数の設定", &g_particle.nNumEffect);

	//初期カラーの設定
	ImGui::ColorEdit4(u8"初期カラーの設定", g_particle.colStart);

	//テクスチャの設定
	ImGui::Combo(u8"テクスチャの設定", &g_particle.effectinfo.nTexPass, c_pTextureName, TEXTURE_MAX, TEXTURE_MAX);

	//ループのオンオフ
	ImGui::Checkbox(u8"ループ", &g_particle.bLoop);

	//描画モードの設定
	ImGui::RadioButton(u8"加算合成", &g_particle.nDrawmode, DRAWMODE_ADD); ImGui::SameLine();
	ImGui::RadioButton(u8"減算合成", &g_particle.nDrawmode, DRAWMODE_SAD); ImGui::SameLine();
	ImGui::RadioButton(u8"合成なし", &g_particle.nDrawmode, DRAWMODE_DEFAULT);

	//パーティクルを発生させる
	if (ImGui::Button("SetParticle"))
	{
		SetParticle(g_particle);
	} ImGui::SameLine();

	//インデックス指定調整ウィンドウの生成
	ImGui::Checkbox("Index", &g_bIndexWindow);
	if(g_bIndexWindow)
	{
		SetParticleWindowIndex();
	}

	//パーティクルウィンドウの終了
	ImGui::End();
}

//==========================================
//  インデックス指定操作
//==========================================
void SetParticleWindowIndex()
{
	//パーティクル情報を取得する
	PARTICLE *pPraticle = GetParticleData();

	//指定調整ウィンドウの生成
	ImGui::Begin(u8"インデックス指定で調整する");

	//全パーティクルのツリーを生成
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pPraticle++)
	{
		//表示用文字列の設定
		char aString[64];
		sprintf(&aString[0], "Index [ %d ]", nCntParticle);

		if (ImGui::CollapsingHeader(&aString[0]))
		{
			if (pPraticle->bUse)
			{
				//テキストの表示
				ImGui::Text(u8"Particle[ %d ]情報", nCntParticle);

				//発生位置の設定
				ImGui::DragFloat3(u8"発生位置", pPraticle->pos);

				//移動量の設定
				ImGui::DragFloat3(u8"移動量", pPraticle->move);

				//拡散の設定
				ImGui::DragFloat3(u8"拡散角", pPraticle->diffuse);

				//サイズの設定
				ImGui::DragFloat3(u8"サイズ", pPraticle->size);

				//寿命の設定
				ImGui::InputInt(u8"パーティクル寿命の設定", &pPraticle->nLife);

				//寿命の設定
				ImGui::InputInt(u8"エフェクト寿命の設定", &pPraticle->nEffectLife);

				//発生数の設定
				ImGui::InputInt(u8"発生数の設定", &pPraticle->nNumEffect);

				//初期カラーの設定
				ImGui::ColorEdit4(u8"初期カラーの設定", pPraticle->colStart);

				//テクスチャの設定
				ImGui::Combo(u8"テクスチャの設定", &pPraticle->effectinfo.nTexPass, c_pTextureName, TEXTURE_MAX, TEXTURE_MAX);

				//ループのオンオフ
				ImGui::Checkbox(u8"ループ", &pPraticle->bLoop); ImGui::SameLine();

				//パーティクルの削除
				if (ImGui::Button(u8"消去"))
				{
					pPraticle->bLoop = false;
					pPraticle->bUse = false;
				}

				//描画モードの設定
				ImGui::RadioButton(u8"加算合成", &pPraticle->nDrawmode, DRAWMODE_ADD); ImGui::SameLine();
				ImGui::RadioButton(u8"減算合成", &pPraticle->nDrawmode, DRAWMODE_SAD); ImGui::SameLine();
				ImGui::RadioButton(u8"合成なし", &pPraticle->nDrawmode, DRAWMODE_DEFAULT);

			}
			else
			{
				//不使用状態を表示
				ImGui::Text(u8"Particle[ %d ] = false", nCntParticle); ImGui::SameLine();
				//パーティクルを発生させる
				if (ImGui::Button("SetParticle"))
				{
					SetParticle(*pPraticle);
				}
			}
		}
	}

	//指定調整ウィンドウの終了
	ImGui::End();
}

//==========================================
//  カメラウィンドウの生成
//==========================================
void SetCameraWindow()
{
	//カメラウィンドウの生成
	ImGui::Begin(u8"カメラ位置の管理");

	//視点の操作
	ImGui::DragFloat3("posV", (float*)&g_posV);
	ImGui::DragFloat3("posR", (float*)&g_posR);

	//カメラウィンドウの終了
	ImGui::End();
}

//==========================================
//  デバッグウィンドウの生成
//==========================================
void SetDebugWindow()
{
	//デバッグウィンドウの生成
	ImGui::Begin(u8"デバッグ表示");

	//エフェクトの使用数を表示
	ImGui::Text("EffectNum = %d", GetEffectNum());

	//パーティクルの使用数を表示
	ImGui::Text("ParticleNum = %d", GetParticleNum());

	//デバッグウィンドウの終了
	ImGui::End();
}
