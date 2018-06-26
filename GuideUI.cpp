//=============================================================================
//
// �K�C�hUI�N���X <Guide.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "GuideUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----����������--------
void UICGuide::Init(void)
{
	TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Active = false;

	this->LoadTexture(UI_TEX_GUIDE);

	this->LoadTextureStatus(80.0f, 20.0f, 1.0f);

	this->MakeVertex();
}

//----�X�V--------
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

//----�`�揈��--------
void UICGuide::Draw(void)
{
	this->DrawBillboard();
}

//----�I������--------
void UICGuide::Uninit(void)
{
	this->ReleaseBuffer();
}

//----�Z�b�g--------
void UICGuide::SetGuideUI(D3DXVECTOR3 pos)
{
	Active = true;
	Position = pos;
	TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetVertex(TexColor);
}
