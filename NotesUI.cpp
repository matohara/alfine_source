//=============================================================================
//
// ノーツUIクラス <Notes.cpp>
// Author : 初 景新
//
//=============================================================================
#include "NotesUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
/* Notes & Lane */
#define NL_CHECK_POS_X	(SCREEN_CENTER_X)
#define NL_CHECK_POS_Y	(64)
#define NL_SIZE_X		(480)
#define NL_SIZE_Y		(60)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----初期化処理--------
void UICNotes::Init(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	Active = false;

	this->LoadTexture(UI_TEX_NOTES);

	this->MakeVertex(Size.x, Size.y, Position.x, Position.y);
}

//----更新--------
void UICNotes::Update(void)
{
	Position.x -= (SCREEN_CENTER_X + NOTES_SIZE_X) / 300.0f;

	SetVertex(Size.x, Size.y, Position.x, Position.y);

	if (Position.x <= NL_CHECK_POS_X)
	{
		SetVertex(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	}

	if (Position.x <= -Size.x)
	{
		Active = false;
	}
}

//----描画処理--------
void UICNotes::Draw(void)
{
	this->class_ObjectU::Draw();
}

//----終了処理--------
void UICNotes::Uninit(void)
{
	this->ReleaseBuffer();
}

//----リセット--------
void UICNotes::ReSet(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}



//----初期化処理--------
void UICNotesLane::Init(void)
{
	this->class_ObjectU::LoadTexture(UI_TEX_LANE);

	this->class_ObjectU::MakeVertex(NL_SIZE_X, NL_SIZE_Y, NL_CHECK_POS_X, NL_CHECK_POS_Y);
}

//----更新--------
//void UICNotesLane::Update(void)


//----描画処理--------
void UICNotesLane::Draw(void)
{
	this->class_ObjectU::Draw();
}

//----終了処理--------
void UICNotesLane::Uninit(void)
{
	this->ReleaseBuffer();
}


