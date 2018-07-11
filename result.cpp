//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 初 景新
//
//=============================================================================
#include "result.h"
#include "Library\Input.h"
#include "Library\Fade.h"
#include "Library\ObjectBase2D.h"
#include "HPUI.h"
#include "Game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_TEX_GAMECLEAR "data/TEXTURE/SCENE/GameClear.png"
#define RESULT_TEX_GAMEOVER "data/TEXTURE/SCENE/GameOver.png"

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
C2DObject     ResultBlack;
C2DObject     ResultBack;
C2DObject     ResultClearUI;
UI2DAnimation ResultUI[2];
UICHitPoint   ResultHPUI;

RESULTSCENE ResultScene = RS_CLEAR;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	ResultScene = RS_CLEAR;

	ResultBlack.Init(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	ResultBack.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 480, 180, RESULT_TEX_BACK);
	if (GetPlayerHP() > 0)
		ResultClearUI.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 250, 250, RESULT_TEX_GAMECLEAR);
	else
		ResultClearUI.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 250, 250, RESULT_TEX_GAMEOVER);
	ResultUI[0].Init(RelativeSX(0.3f), SCREEN_CENTER_Y, 100, 100, RESULT_TEX_RETRY);
	ResultUI[1].Init(RelativeSX(0.7f), SCREEN_CENTER_Y, 150, 150, RESULT_TEX_GOMENU);

	// HPUI
	ResultHPUI.Init(HPUI_MAX_HP, SCREEN_CENTER_X, RelativeSY(0.4f), 25, 25);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	ResultBlack.Release();
	ResultBack.Release();
	ResultClearUI.Release();
	ResultUI[0].Release();
	ResultUI[1].Release();
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
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			ResultScene = RS_RETRY;
		}
		break;
	case RS_RETRY:
		ResultUI[0].Animation01();
		if ((GetKeyboardTrigger(DIK_LEFT))      || (GetKeyboardTrigger(DIK_RIGHT)) || 
			(IsButtonTriggered(0, LSTICK_LEFT)) || (IsButtonTriggered(0, LSTICK_RIGHT)))
		{
			ResultScene = RS_GOMENU;
			ResultUI[0].ResetData(0);
		}
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			ResultScene = RS_RETRY;
			CSFade::SetFade(SCENE_GAME);
		}
		break;
	case RS_GOMENU:
		ResultUI[1].Animation01();
		if ((GetKeyboardTrigger(DIK_LEFT))      || (GetKeyboardTrigger(DIK_RIGHT)) || 
			(IsButtonTriggered(0, LSTICK_LEFT)) || (IsButtonTriggered(0, LSTICK_RIGHT)))
		{
			ResultScene = RS_RETRY;
			ResultUI[1].ResetData(0);
		}
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			CSFade::SetFade(SCENE_STAGESELECT);
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


