//==========================================
//
//  パーティクル制御(particle.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//==========================================
//  パーティクル構造体定義
//==========================================
typedef struct
{	
	//原点
	D3DXVECTOR3 pos; //発生原点
	D3DXVECTOR3 posError; //発生原点誤差

	//速度
	D3DXVECTOR3 moveStart; //初期速度
	D3DXVECTOR3 moveAcceleration; //最終速度
	D3DXVECTOR3 moveError; //速度誤差

	//サイズ
	D3DXVECTOR3 size; //初期サイズ
	D3DXVECTOR3 magnification; //最終サイズ

	//回転
	D3DXVECTOR3 rot; //初期角度(ポリゴン)
	D3DXVECTOR3 rotate; //初期回転速度(ポリゴン)

	//色
	D3DXCOLOR colorStart; //初期カラー
	D3DXCOLOR colorEnd; //最終カラー

	//寿命
	int nLife_P; //パーティクルライフ
	int nLife_E; //エフェクトライフ

	//その他
	float fGravity; //重力
	bool bLoop; //ループon/off
	bool bCollision; //当たり判定

	//形状
	/*
	選択式
	選択内容によって別ウィンドウを表示
	形状ごとのステータスを設定する
	*/

}ParticleData;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void SetParticle(void);

#endif
