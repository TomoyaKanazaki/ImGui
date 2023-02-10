//==========================================
//
//  パーティクル制御(particle.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "particle.h"
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
	D3DXVECTOR3 rot; //角度
	D3DXVECTOR3 rotError; //角度誤差
	D3DXVECTOR3 rotSpeed; //回転速度
	D3DXVECTOR3 rotSpeedError; //回転角度
	D3DXCOLOR colStart; //初期カラー
	D3DXCOLOR colStartError; //初期カラー誤差
	D3DXCOLOR colEnd; //最終カラー
	D3DXCOLOR colEndError; //最終カラー誤差
	int nLife; //パーティクルの寿命
	int nNumEffect; //1F毎の発生数
	float fGravity; //重力の値
	bool bLoop; //ループの切り替え
	bool bCollision; //当たり判定の切り替え
	DRAWMODE drawmode; //ドローモード
	EFFECT effectinfo; //エフェクトデータ
}PARTICLE;

//==========================================