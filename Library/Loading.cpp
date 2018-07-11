//=============================================================================
//
// ���[�f�B���O��ʏ��� [Loading.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Loading.h"
#include "Input.h"
#include "Fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOADING_TEX_BACK "data/TEXTURE/SCENE/LoadBack.jpg"
#define LOADING_TEX_GAGE "data/TEXTURE/SCENE/LoadBox.jpg"
#define LOADING_TEX_TEXT "data/TEXTURE/SCENE/load.png"


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----������--------
void CNowLoading::Init(GAMESCENE scene)
{
//	NextScene = scene;
	Back.LoadTexture(LOADING_TEX_BACK);
	Text.Init(RelativeSX(0.8f), RelativeSY(0.8f), 200, 10, LOADING_TEX_TEXT);
	PercentGage.Init(LOADING_TEX_GAGE, LOADING_TEX_GAGE);
	PercentGage.Init(RelativeSX(0.8f), RelativeSY(0.85f), 200, 20);
	PercentGage.Frame.SetVertex(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	PercentGage.Gage.SetVertex(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
}

//----�I��--------
void CNowLoading::Uninit(void)
{
	Back.Release();
	Text.Release();
	PercentGage.Uninit();
}

//----�X�V--------
void CNowLoading::Progress(int per)
{
	/* �X�V */
	float percent = (float)per / 100.0f;
	PercentGage.Update(percent);

	/* �`�� */
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(pDevice->BeginScene()))
	{

		Back.Draw();
		PercentGage.Draw();
		Text.Draw();

		// Direct3D�ɂ��`��̏I��
		pDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	pDevice->Present(NULL, NULL, NULL, NULL);
}


