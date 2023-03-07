//==========================================
//
//  エフェクトの処理(effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect.h"
#include "polygon.h"
#include "texture.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_EFFECT (2048) //エフェクトの最大値

//==========================================
//  グローバル変数宣言
//==========================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];

//==========================================
//  初期化処理
//==========================================
void InitEffect()
{
	//変数の初期化
	ZeroMemory(&g_aEffect[0], sizeof(EFFECT) * MAX_EFFECT);
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_aEffect[nCnt].nDrawmode = DRAWMODE_DEFAULT;
		g_aEffect[nCnt].nTexPass = TEXTURE_EFFECT_DEFAULT;
	}

	//ポリゴンの初期化
	g_pVtxBuffEffect = Init_3D_Polygon(MAX_EFFECT);
}

//==========================================
//  終了処理
//==========================================
void UninitEffect()
{
	//ポリゴンの破棄
	UninitPolygon(&g_pVtxBuffEffect);
}

//==========================================
//  更新処理
//==========================================
void UpdateEffect()
{
	//エフェクトの更新
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//使用/不使用の判定
		if (g_aEffect[nCnt].bUse)
		{
			//移動
			g_aEffect[nCnt].pos += g_aEffect[nCnt].move;

			//寿命の減少
			if (g_aEffect[nCnt].nLife <= 0)
			{
				//不使用に設定
				g_aEffect[nCnt].bUse = false;
			}
			g_aEffect[nCnt].nLife--;
		}
	}
}

//==========================================
//  描画処理
//==========================================
void DrawEffect()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxView; //ビューマトリックス取得用

	//ライティングを無効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse)
		{
			//アルファブレンディングを設定
			switch (g_aEffect[nCnt].nDrawmode)
			{
			case DRAWMODE_ADD: //加算合成
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			case DRAWMODE_SAD: //減算合成
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			default: //なし
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCnt].mtxWorld);

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aEffect[nCnt].mtxWorld, NULL, &mtxView);

			//値の補正
			g_aEffect[nCnt].mtxWorld._41 = 0.0f;
			g_aEffect[nCnt].mtxWorld._42 = 0.0f;
			g_aEffect[nCnt].mtxWorld._43 = 0.0f;

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCnt].pos.x, g_aEffect[nCnt].pos.y, g_aEffect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCnt].mtxWorld, &g_aEffect[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCnt].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, GetTexture(g_aEffect[nCnt].nTexPass));

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}

		//アルファテストの無効化
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//Zテストの有効化
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//アルファブレンディングをの設定を元に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	}

	//ライティングを有効化する
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  設定処理
//==========================================
void SetEffect(EFFECT effectdata)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse == false)
		{
			//エフェクトデータを設定する
			g_aEffect[nCnt] = effectdata;

			//頂点座標を設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCnt].size.x, g_aEffect[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCnt].size.x, g_aEffect[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCnt].size.x, -g_aEffect[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCnt].size.x, -g_aEffect[nCnt].size.y, 0.0f);

			//頂点カラーを設定
			for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
			{
				pVtx[nCntVtx].col = g_aEffect[nCnt].colorStart;
			}

			//使用設定
			g_aEffect[nCnt].bUse = true;

			break;
		}
		//頂点データを進める
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//==========================================
//  エフェクトの使用数を取得
//==========================================
int GetEffectNum()
{
	//ローカル変数宣言
	int nNum = 0;

	//使用数のカウント
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_aEffect[nCnt].bUse)
		{
			nNum++;
		}
	}

	return nNum;
}
