//=============================================================================
//
// �X�e�[�^�X�o�[UI�N���X <StatusBarUI.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "StatusBarUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----����������--------
void UICNvX::Init(float size, float posX, float posY)
{
	N.LoadTexture(UI_TEX_NUMBER);
	X.LoadTexture(UI_TEX_NUMBER);
	Slash.LoadTexture(UI_TEX_SLASH);

	N.Init(UI_NvX_N_SIZE_X * size, UI_NvX_N_SIZE_Y * size, UI_NvX_N_POS_X + posX, UI_NvX_N_POS_Y + posY);
	X.Init(UI_NvX_X_SIZE_X * size, UI_NvX_X_SIZE_Y * size, UI_NvX_X_POS_X + posX, UI_NvX_X_POS_Y + posY);
	Slash.Init(UI_NvX_SLASH_SIZE_X * size, UI_NvX_SLASH_SIZE_Y * size, 
		UI_NvX_SLASH_POS_X + posX, UI_NvX_SLASH_POS_Y + posY);

	N.SetNumber(1);
	X.SetNumber(4);
}

//----�X�V--------
void UICNvX::Update(int num)
{
	N.SetNumber(num);
}

//----�`�揈��--------
void UICNvX::Draw(void)
{
	N.Draw();
	X.Draw();
	Slash.Draw();
}

//----�I������--------
void UICNvX::Uninit(void)
{
	N.ReleaseBuffer();
	X.ReleaseBuffer();
	Slash.ReleaseBuffer();
}

