//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 初 景新
//
//=============================================================================
#include "title.h"
#include "../../input.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEX_BACK "data/TEXTURE/SCENE/Title.jpg"
#define TITLE_TEX_LOGO "data/TEXTURE/SCENE/TitleLogo.png"
#define TITLE_TEX_PRESSKEY "data/TEXTURE/SCENE/Press.png"
#define TITLE_TEX_NEWGAME "data/TEXTURE/SCENE/NewGame.png"
#define TITLE_TEX_COUNTINUE "data/TEXTURE/SCENE/Countinue.png"
#define TITLE_TEX_OPTION "data/TEXTURE/SCENE/Option.png"

enum STATUSTITLE
{
	ST_PRESSKEY = 0,
	ST_NEWGAME,
	ST_COUNTINUE,
	ST_OPTION,
	ST_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
C2DUIPolygon TitleBack;
C2DUIPolygon TitleLogo;
C2DUIMenuLogo TitlePressKey;
C2DUIMenuLogo TitleMenuLogo[3];
STATUSTITLE TitleStatus = ST_PRESSKEY;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	TitleBack.Init(TITLE_TEX_BACK);
	TitleLogo.Init(225, 135, SCREEN_CENTER_X, 150, TITLE_TEX_LOGO);	// 1024 : 613 (1.67)
	TitlePressKey.Init(100, 20, SCREEN_CENTER_X, RelativeSY(0.8f), TITLE_TEX_PRESSKEY);	// 500 : 100 (5)
	TitleMenuLogo[0].Init(75, 15, SCREEN_CENTER_X, RelativeSY(0.65f), TITLE_TEX_NEWGAME);	// 400 : 80 (5)
	TitleMenuLogo[1].Init(75, 15, SCREEN_CENTER_X, RelativeSY(0.75f), TITLE_TEX_COUNTINUE);	// 400 : 80 (5)
	TitleMenuLogo[2].Init(50, 20, SCREEN_CENTER_X, RelativeSY(0.85f), TITLE_TEX_OPTION);	// 250 : 100 (2.5)

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	TitleBack.ReleaseBuffer();
	TitleLogo.ReleaseBuffer();
	TitlePressKey.ReleaseBuffer();
	TitleMenuLogo[0].ReleaseBuffer();
	TitleMenuLogo[1].ReleaseBuffer();
	TitleMenuLogo[2].ReleaseBuffer();
}

//=============================================================================
// 更新処理
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
			TitleStatus = ST_OPTION;
			TitleMenuLogo[0].ReSet();
			break;
		case ST_COUNTINUE:
			break;
		case ST_OPTION:
			TitleStatus = ST_NEWGAME;
			TitleMenuLogo[2].ReSet();
			break;
		}
	}

	if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
	{
		switch (TitleStatus)
		{
		case ST_NEWGAME:
			TitleStatus = ST_OPTION;
			TitleMenuLogo[0].ReSet();
			break;
		case ST_COUNTINUE:
			break;
		case ST_OPTION:
			TitleStatus = ST_NEWGAME;
			TitleMenuLogo[2].ReSet();
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
		TitleMenuLogo[0].Animation02();
		break;
	case ST_COUNTINUE:
		break;
	case ST_OPTION:
		TitleMenuLogo[2].Animation01();
		TitleMenuLogo[2].Animation02();
		break;
	}
}

//=============================================================================
// 描画処理
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

