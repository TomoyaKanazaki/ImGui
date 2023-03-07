//==========================================
//
//  パーティクル制御(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"
#include "effect.h"

//==========================================
//  パーティクル構造体定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //発生原点
	D3DXVECTOR3 posError; //発生原点誤差
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 moveError; //移動量誤差
	D3DXVECTOR3 acceleration; //加速度
	D3DXVECTOR3 accelerationError; //加速度誤差
	D3DXVECTOR3 size; //ポリゴンサイズ
	D3DXVECTOR3 sizeError; //ポリゴンサイズ誤差
	D3DXVECTOR3 magnification; //拡大率
	D3DXVECTOR3 magnificationError; //拡大率誤差
	D3DXCOLOR colStart; //初期カラー
	D3DXCOLOR colStartError; //初期カラー誤差
	D3DXCOLOR colEnd; //最終カラー
	D3DXCOLOR colEndError; //最終カラー誤差
	int nLife; //パーティクルの寿命
	int nEffectLife; //エフェクトの寿命
	int nNumEffect; //1F毎の発生数
	int nDrawmode; //ドローモード
	float fGravity; //重力の値
	bool bUse; //使用不使用の設定
	bool bLoop; //ループの切り替え
	bool bCollision; //当たり判定の切り替え
	EFFECT effectinfo; //エフェクトデータ
}PARTICLE;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle
(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 move,
	D3DXVECTOR3 size,
	D3DXCOLOR colStart,
	int nLife,
	int nEffectLife,
	int nNumEffect,
	int nDrawmode,
	int nTexPass,
	bool bLoop
);
int GetParticleNum(void);

#endif
