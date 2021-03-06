//=============================================================================
//
// デバッグ表示処理 [DebugProcess.h]
// Author : 初 景新
//
//=============================================================================
#ifndef __DEBUGPROCESS_INCLUDE_H__
#define __DEBUGPROCESS_INCLUDE_H__

#include "LinkLibrary.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProcess(void);
void UninitDebugProcess(void);
void UpdateDebugProcess(void);
void DrawDebugProcess(void);

void PrintDebugProcess(char *fmt,...);


#endif