//=============================================================================
//
// ステータスバーUIクラス <StatusBarUI.cpp>
// Author : 初 景新
//
//=============================================================================
#include "StatusBarUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----初期化処理--------
void UICNvX::Init(float size, float posX, float posY)
{
	LPDIRECT3DTEXTURE9 tex;
	N.LoadTexture(UI_TEX_NUMBER);
	N.GetTexture(&tex);
	X.LoadTexture(tex);
	Slash.LoadTexture(tex);

	N.SetStatus(UI_NvX_N_SIZE_X * size, UI_NvX_N_SIZE_Y * size, UI_NvX_N_POS_X + posX, UI_NvX_N_POS_Y + posY);
	X.SetStatus(UI_NvX_X_SIZE_X * size, UI_NvX_X_SIZE_Y * size, UI_NvX_X_POS_X + posX, UI_NvX_X_POS_Y + posY);
	Slash.SetStatus(UI_NvX_SLASH_SIZE_X * size, UI_NvX_SLASH_SIZE_Y * size,
		UI_NvX_SLASH_POS_X + posX, UI_NvX_SLASH_POS_Y + posY);

	N.SetNumber(1);
	X.SetNumber(3);
	Slash.SetNumber(0);
}

//----更新--------
void UICNvX::Update(int num)
{
	N.SetNumber(num);
}

//----描画処理--------
void UICNvX::Draw(void)
{
	N.Draw();
	X.Draw();
	Slash.Draw();
}

//----終了処理--------
void UICNvX::Uninit(void)
{
	N.Release();
	X.Release();
	Slash.Release();
}

