//=============================================================================
//
// ガイドUIクラス <Guide.cpp>
// Author : 初 景新
//
//=============================================================================
#include "GuideUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----初期化処理--------
void UICGuide::Init(void)
{
	TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Active = false;

	this->LoadTexture(UI_TEX_GUIDE);

	this->LoadTextureStatus(80.0f, 20.0f, 1.0f);

	this->MakeVertex();
}

//----更新--------
int UICGuide::Update(void)
{
	TexColor.a -= 0.05f;
	if (TexColor.a <= 0.0f)
	{
		Active = false;
		return 1;
	}
	this->SetVertex(TexColor);
	return 0;
}

//----描画処理--------
void UICGuide::Draw(void)
{
	this->DrawBillboard();
}

//----終了処理--------
void UICGuide::Uninit(void)
{
	this->ReleaseBuffer();
}

//----セット--------
void UICGuide::SetGuideUI(D3DXVECTOR3 pos)
{
	Active = true;
	Position = pos;
	TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetVertex(TexColor);
}

