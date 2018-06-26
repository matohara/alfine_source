//=============================================================================
//
// �m�[�cUI�N���X <Notes.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "NotesUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
/* Notes & Lane */
#define NL_CHECK_POS_X	(SCREEN_CENTER_X)
#define NL_CHECK_POS_Y	(64)
#define NL_SIZE_X		(480)
#define NL_SIZE_Y		(60)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----����������--------
void UICNotes::Init(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	Active = false;

	this->LoadTexture(UI_TEX_NOTES);

	this->MakeVertex(Size.x, Size.y, Position.x, Position.y);
}

//----�X�V--------
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

//----�`�揈��--------
void UICNotes::Draw(void)
{
	this->class_ObjectU::Draw();
}

//----�I������--------
void UICNotes::Uninit(void)
{
	this->ReleaseBuffer();
}

//----���Z�b�g--------
void UICNotes::ReSet(void)
{
	Position = D3DXVECTOR2(SCREEN_WIDTH + NOTES_SIZE_X, NL_CHECK_POS_Y);
	Size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
	SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}



//----����������--------
void UICNotesLane::Init(void)
{
	this->class_ObjectU::LoadTexture(UI_TEX_LANE);

	this->class_ObjectU::MakeVertex(NL_SIZE_X, NL_SIZE_Y, NL_CHECK_POS_X, NL_CHECK_POS_Y);
}

//----�X�V--------
//void UICNotesLane::Update(void)


//----�`�揈��--------
void UICNotesLane::Draw(void)
{
	this->class_ObjectU::Draw();
}

//----�I������--------
void UICNotesLane::Uninit(void)
{
	this->ReleaseBuffer();
}


