//==========================================
//
//  エフェクトの処理(effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"

//==========================================
//  マクロ定義
//==========================================
#define MAX_TEXT (128) //パスの最大文字数

//==========================================
//  列挙型定義
//==========================================
typedef enum
{
	DRAWMODE_DEFAULT = 0, //デフォルトの描画
	DRAWMODE_ADD, //加算合成
	DRAWMODE_SAD, //減算合成
	DRAWMODE_MAX
}DRAWMODE;

//==========================================
//  構造体定義
//==========================================
typedef struct
{
	D3DXVECTOR3 pos; //発生原点
	D3DXVECTOR3 move; //移動量
	D3DXVECTOR3 moveAcceleration; //加速度
	D3DXVECTOR3 size; //ポリゴンサイズ
	D3DXVECTOR3 magnification; //ポリゴンサイズ拡大率
	D3DXCOLOR colorStart; //初期カラー
	D3DXCOLOR colorEnd; //最終カラー
	int nLife; //寿命
	int nDrawmode; //描画モード
	float fGravity; //重力
	bool bCollision; //当たり判定
	bool bUse; //使用/不使用
	D3DXMATRIX mtxWorld; //ワールドマトリックス
}EFFECT;

//==========================================
//  プロトタイプ宣言
//==========================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(EFFECT effectdata);
int GetEffectNum(void);

#endif
