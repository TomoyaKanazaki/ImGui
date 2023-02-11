//==========================================
//
//  パーティクル制御(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_PARTICLE (32) //パーティクル最大数

//==========================================
//  グローバル変数宣言
//==========================================
PARTICLE g_aParticle[MAX_PARTICLE];

//==========================================
//  初期化処理
//==========================================
void InitParticle()
{
	//変数の初期化
	ZeroMemory(&g_aParticle[0], sizeof(PARTICLE) * MAX_PARTICLE);
	
	//不使用状態に初期化する
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].bUse = false;
	}
}

//==========================================
//  終了処理
//==========================================
void UninitParticle()
{

}

//==========================================
//  更新処理
//==========================================
void UpdateParticle()
{

}

//==========================================
//  描画処理
//==========================================
void DrawParticle()
{

}

//==========================================
//  設定処理
//==========================================
void SetParticle
(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 move,
	//D3DXVECTOR3 acceleration,
	D3DXVECTOR3 size,
	//D3DXVECTOR3 magnification,
	int nLife,
	int nNumEffect,
	bool bLoop
)
{
	//パーティクルの設定
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			//原点の設定
			g_aParticle[nCnt].effectinfo.pos = pos;

			//移動量の設定
			g_aParticle[nCnt].effectinfo.move = move;

			//大きさの設定
			g_aParticle[nCnt].effectinfo.size = size;

			//寿命の設定
			g_aParticle[nCnt].nLife = nLife;

			//使用状態を切り替え
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}
