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
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//エフェクトの情報を設定
			for (int nCntEffect = 0; nCntEffect < g_aParticle[nCnt].nNumEffect; nCntEffect++)
			{
				//エフェクトの発生位置を設定
				g_aParticle[nCnt].effectinfo.pos = g_aParticle[nCnt].pos;

				//エフェクトの移動量を設定
				if (g_aParticle[nCnt].move.x != 0) //x
				{
					g_aParticle[nCnt].effectinfo.move.x = (float)(rand() % (int)(g_aParticle[nCnt].move.x * 2.0f) - g_aParticle[nCnt].move.x);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.x = 0;
				}

				if (g_aParticle[nCnt].move.y != 0) //y
				{
					g_aParticle[nCnt].effectinfo.move.y = (float)(rand() % (int)(g_aParticle[nCnt].move.y * 2.0f) - g_aParticle[nCnt].move.y);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.y = 0;
				}

				if (g_aParticle[nCnt].move.z != 0) //z
				{
					g_aParticle[nCnt].effectinfo.move.z = (float)(rand() % (int)(g_aParticle[nCnt].move.z * 2.0f) - g_aParticle[nCnt].move.z);
				}
				else
				{
					g_aParticle[nCnt].effectinfo.move.z = 0;
				}

				//エフェクトの大きさの設定
				g_aParticle[nCnt].effectinfo.size = g_aParticle[nCnt].size;
	
				//エフェクトの初期カラーを設定
				g_aParticle[nCnt].effectinfo.colorStart = g_aParticle[nCnt].colStart;
	
				//エフェクトの寿命を設定
				g_aParticle[nCnt].effectinfo.nLife = g_aParticle[nCnt].nEffectLife;
	
				//描画モードの設定
				g_aParticle[nCnt].effectinfo.nDrawmode = g_aParticle[nCnt].nDrawmode;

				//エフェクトの呼び出し
				SetEffect(g_aParticle[nCnt].effectinfo);
			}

			//寿命がなくなったら不使用にする
			if (g_aParticle[nCnt].nLife <= 0)
			{
				//ループ設定の適用
				g_aParticle[nCnt].bUse = g_aParticle[nCnt].bLoop;
			}

			//寿命を減少
			g_aParticle[nCnt].nLife--;
		}
	}
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
	D3DXCOLOR colStart,
	int nLife,
	int nEffectLife,
	int nNumEffect,
	int nDrawmode,
	bool bLoop
)
{
	//パーティクルの設定
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			//原点の設定
			g_aParticle[nCnt].pos = pos;

			//移動量の設定
			g_aParticle[nCnt].move = move;

			//大きさの設定
			g_aParticle[nCnt].size = size;

			//初期カラーの設定
			g_aParticle[nCnt].colStart = colStart;  

			//パーティクル寿命の設定
			g_aParticle[nCnt].nLife = nLife;

			//エフェクト寿命の設定
			g_aParticle[nCnt].nEffectLife = nEffectLife;

			//エフェクト発生数の設定
			g_aParticle[nCnt].nNumEffect = nNumEffect;

			//描画モードの設定
			g_aParticle[nCnt].nDrawmode = nDrawmode;

			//ループの設定
			g_aParticle[nCnt].bLoop = bLoop;

			//使用状態を切り替え
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}

//==========================================
//  パーティクルの使用数を取得
//==========================================
int GetParticleNum()
{
	//ローカル変数宣言
	int nNum = 0;

	//使用数のカウント
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			nNum++;
		}
	}

	return nNum;
}
