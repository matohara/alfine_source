//=============================================================================
//
// ステージセレクト処理 [StageSelect.cpp]
// Author : 初 景新
//
//=============================================================================
#include "title.h"
#include "../../input.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/Tutorial.jpg"
#define STAGESELECT_TEX_TUTORIAL_LOGO "data/TEXTURE/STAGEVIEW/TutorialLogo.png"

enum STATUSSTAGESELECT
{
	SSS_TUTORIAL = 0,
	SSS_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
C2DUIPolygon StageSelectBack;
C2DUIPolygon StageSelectLogo;
STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStageSelect(void)
{
	StageSelectBack.Init(STAGESELECT_TEX_TUTORIAL);
	StageSelectLogo.Init(240, 60, RelativeSX(0.7f), SCREEN_CENTER_Y, STAGESELECT_TEX_TUTORIAL_LOGO);	// 1024 : 256 (4)

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.ReleaseBuffer();
	StageSelectLogo.ReleaseBuffer();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStageSelect(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (SSStastus)
		{
		case SSS_TUTORIAL:
			CSFade::SetFade(SCENE_GAME);
			break;
		}
	}

	if (GetKeyboardTrigger(DIK_UP))
	{

	}

	if (GetKeyboardTrigger(DIK_DOWN))
	{

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStageSelect(void)
{
	StageSelectBack.Draw();
	StageSelectLogo.Draw();
}

