//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#ifndef __FADE_INCLUDE_H__
#define __FADE_INCLUDE_H__

#include "../../main.h"

//*************************************
// フェードの状態
//*************************************
typedef enum
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_MAX
} FADE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, GAMESCENE scene);
FADE GetFade(void);

#endif
