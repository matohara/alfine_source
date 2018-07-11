//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "title.h"
#include "Library\Input.h"
#include "Library\Fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEX_BACK      "data/�^�C�g��/Title.jpg"
#define TITLE_TEX_LOGO      "data/�^�C�g��/TitleLogo.png"
#define TITLE_TEX_PRESSKEY  "data/�^�C�g��/Press.png"
#define TITLE_TEX_NEWGAME   "data/�^�C�g��/NewGame.png"
#define TITLE_TEX_COUNTINUE "data/�^�C�g��/Countinue.png"
#define TITLE_TEX_OPTION    "data/�^�C�g��/Option.png"

enum STATUSTITLE
{
	ST_PRESSKEY = 0,
	ST_NEWGAME,
	ST_COUNTINUE,
	ST_OPTION,
	ST_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UIBackGround  TitleBack;
C2DObject     TitleLogo;
UI2DAnimation TitlePressKey;
UI2DAnimation TitleMenuLogo[3];
STATUSTITLE   TitleStatus = ST_PRESSKEY;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	TitleBack.LoadTexture(TITLE_TEX_BACK);
	TitleLogo.Init(       SCREEN_CENTER_X,               170, 250, 150, TITLE_TEX_LOGO);    // 1024 : 613 (1.67)
	TitlePressKey.Init(   SCREEN_CENTER_X, RelativeSY( 0.8f), 100,  20, TITLE_TEX_PRESSKEY);  // 500 : 100 (5)
	TitleMenuLogo[0].Init(SCREEN_CENTER_X, RelativeSY(0.65f),  75,  15, TITLE_TEX_NEWGAME);   // 400 : 80 (5)
	TitleMenuLogo[1].Init(SCREEN_CENTER_X, RelativeSY(0.75f),  75,  15, TITLE_TEX_COUNTINUE); // 400 : 80 (5)
	TitleMenuLogo[2].Init(SCREEN_CENTER_X, RelativeSY(0.85f),  50,  20, TITLE_TEX_OPTION);	  // 250 : 100 (2.5)
	TitleMenuLogo[0].SetVertex(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	TitleBack.Release();
	TitleLogo.Release();
	TitlePressKey.Release();
	TitleMenuLogo[0].Release();
	TitleMenuLogo[1].Release();
	TitleMenuLogo[2].Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
	{
		switch (TitleStatus)
		{
		case ST_PRESSKEY:
			TitleStatus = ST_NEWGAME;
			break;
		case ST_NEWGAME:
			CSFade::SetFade(SCENE_STAGESELECT);
			break;
		case ST_COUNTINUE:
			break;
		case ST_OPTION:
			break;
		}
	}

	if ((GetKeyboardTrigger(DIK_ESCAPE)) || (IsButtonTriggered(0, BUTTON_B)))
	{
		TitleStatus = ST_PRESSKEY;
	}

	if ((GetKeyboardTrigger(DIK_UP)) || (IsButtonTriggered(0, LSTICK_UP)))
	{
		switch (TitleStatus)
		{
		case ST_NEWGAME:
			TitleMenuLogo[0].ResetData(0);
			TitleMenuLogo[0].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			TitleStatus = ST_OPTION;
			TitleMenuLogo[2].SetVertex(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		case ST_COUNTINUE:
			break;
		case ST_OPTION:
			TitleMenuLogo[2].ResetData(0);
			TitleMenuLogo[2].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			TitleStatus = ST_NEWGAME;
			TitleMenuLogo[0].SetVertex(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		}
	}

	if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
	{
		switch (TitleStatus)
		{
		case ST_NEWGAME:
			TitleMenuLogo[0].ResetData(0);
			TitleMenuLogo[0].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			TitleStatus = ST_OPTION;
			TitleMenuLogo[2].SetVertex(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		case ST_COUNTINUE:
			break;
		case ST_OPTION:
			TitleMenuLogo[2].ResetData(0);
			TitleMenuLogo[2].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			TitleStatus = ST_NEWGAME;
			TitleMenuLogo[0].SetVertex(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		}
	}

	switch (TitleStatus)
	{
	case ST_PRESSKEY:
		TitlePressKey.Animation01();
		break;
	case ST_NEWGAME:
		TitleMenuLogo[0].Animation01();
		break;
	case ST_COUNTINUE:
		break;
	case ST_OPTION:
		TitleMenuLogo[2].Animation01();
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	TitleBack.Draw();
	TitleLogo.Draw();
	switch (TitleStatus)
	{
	case ST_PRESSKEY:
		TitlePressKey.Draw();
		break;
	case ST_NEWGAME:
	case ST_COUNTINUE:
	case ST_OPTION:
		TitleMenuLogo[0].Draw();
		TitleMenuLogo[1].Draw();
		TitleMenuLogo[2].Draw();
		break;
	}
}

