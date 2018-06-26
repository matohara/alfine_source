//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 初 景新
//
//=============================================================================
#include "result.h"
#include "../../input.h"
#include "fade.h"
#include "../class/ObjectBase.h"
#include "../../HPUI.h"
#include "../../Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEX_GAMECLEAR "data/TEXTURE/SCENE/GameClear.png"
#define RESULT_TEX_RETRY "data/TEXTURE/SCENE/Option_G01.png"
#define RESULT_TEX_GOMENU "data/TEXTURE/SCENE/Modoru.png"
#define RESULT_TEX_BACK "data/TEXTURE/UI/OptionFrame.png"

enum RESULTSCENE
{
	RS_CLEAR,
	RS_RETRY,
	RS_GOMENU,
	RS_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
C2DUIPolygon ResultBlack;
C2DUIPolygon ResultBack;
C2DUIPolygon ResultClearUI;
C2DUIMenuLogo ResultUI[2];
UICHitPoint ResultHPUI;

RESULTSCENE ResultScene = RS_CLEAR;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	ResultScene = RS_CLEAR;

	ResultBlack.Init();
	ResultBack.Init(400, 140, RESULT_TEX_BACK);
	ResultClearUI.Init(250, 250, RESULT_TEX_GAMECLEAR);
	ResultUI[0].Init(100, 100, RelativeSX(0.3f), SCREEN_CENTER_Y, RESULT_TEX_RETRY);
	ResultUI[1].Init(150, 150, RelativeSX(0.7f), SCREEN_CENTER_Y, RESULT_TEX_GOMENU);

	// HPUI
	ResultHPUI.Init(HPUI_MAX_HP, 25, 25, SCREEN_CENTER_X, RelativeSY(0.4f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	ResultBlack.ReleaseBuffer();
	ResultBack.ReleaseBuffer();
	ResultClearUI.ReleaseBuffer();
	ResultUI[0].ReleaseBuffer();
	ResultUI[1].ReleaseBuffer();
	ResultHPUI.Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	switch (ResultScene)
	{
	case RS_CLEAR:
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			ResultScene = RS_RETRY;
		}
		break;
	case RS_RETRY:
		ResultUI[0].Animation01();
		if (GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_RIGHT))
		{
			ResultScene = RS_GOMENU;
			ResultUI[0].ReSet();
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			ResultScene = RS_RETRY;
			SetFade(FADE_OUT, SCENE_GAME);
		}
		break;
	case RS_GOMENU:
		ResultUI[1].Animation01();
		if (GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_RIGHT))
		{
			ResultScene = RS_RETRY;
			ResultUI[1].ReSet();
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, SCENE_STAGESELECT);
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	ResultBlack.Draw();

	switch (ResultScene)
	{
	case RS_CLEAR:
		ResultHPUI.Draw(GetPlayerHP());
		ResultClearUI.Draw();
		break;
	case RS_RETRY:
	case RS_GOMENU:
		ResultBack.Draw();
		ResultUI[0].Draw();
		ResultUI[1].Draw();
		break;
	}
}


