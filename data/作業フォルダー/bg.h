//=============================================================================
//
// 背景処理 [bg.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _BG_INCLUDE_H_
#define _BG_INCLUDE_H_

#include "source/class/Aclass_object.h"

// マクロ定義
#define TEXTURE_GAME_BG	_T("data/TEXTURE/FIELD/BG.jpg")	// サンプル用画像
#define BG_SIZE_X		(2000)	// テクスチャサイズ
#define BG_SIZE_Y		(2000)	// 同上
#define BG_POS_X		(0)		// ポリゴンの初期位置X
#define BG_POS_Y		(0)		// 同上

//*****************************************************************************
// クラス設計
//*****************************************************************************
class CBackTexture : public class_ObjectA
{
public:
	CBackTexture() {};
	~CBackTexture() {};

	void SetBGTStatus(float fX, float fY, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif
