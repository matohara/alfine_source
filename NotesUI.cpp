//=============================================================================
//
// ノーツUIクラス <NotesUI.cpp>
// Author : 初 景新
//
//=============================================================================
#include "NotesUI.h"


/* Notes & Lane */
#define NL_CHECK_POS_X	(SCREEN_CENTER_X)
#define NL_CHECK_POS_Y	(64)
#define NL_SIZE_X		(480)
#define NL_SIZE_Y		(60)


//----初期化処理--------
int UICNotes::Init(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	Active = false;

	this->LoadTexture(UI_TEX_NOTES);
	this->MakeVertex(Size.x, Size.y, Position.x, Position.y);
	return 0;
}

//----更新--------
void UICNotes::Update(void)
{
	Position.x -= (SCREEN_CENTER_X + NOTES_SIZE_X) / 300.0f;

	this->ObjectBase2D::SetVertex(Size.x, Size.y, Position.x, Position.y);

	if (Position.x <= NL_CHECK_POS_X)
	{
		SetVertex(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	}

	if (Position.x <= -Size.x)
	{
		Active = false;
	}
}

//----リセット--------
void UICNotes::ReSet(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}



//----初期化処理--------
int UICNotesLane::Init(void)
{
	this->LoadTexture(UI_TEX_LANE);
	this->MakeVertex(NL_SIZE_X, NL_SIZE_Y, NL_CHECK_POS_X, NL_CHECK_POS_Y);
	return 0;
}


