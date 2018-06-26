//=============================================================================
//
// デバッグ表示処理 [DebugProcess.h]
// Author : 初 景新
//
//=============================================================================
#ifndef __DEBUGPROCESS_INCLUDE_H__
#define __DEBUGPROCESS_INCLUDE_H__

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define dbgMAIN			(0x80000000)	// MainDebug(FPS...)
#define dbgHITBOX		(0x40000000)	// ViewHitBox
#define dbgLIGHTING		(0x20000000)	// Render-Lighting(on/off)
#define dbgCAMERA		(0x00000001)	// CameraStatus
#define dbgLIGHT		(0x00000002)	// LightStatus
#define dbgPLAYER		(0x00000004)	// PlayerStatus
#define dbgENEMY		(0x00000008)	// EnemyStatus
#define dbgVIEWCAMERA	(0x00000010)	// ViewCamera
#define dbgVIEWLIGHT	(0x00000020)	// ViewLight
#define dbgBULLETp		(0x00000040)	// PlayerBulletStatus
#define dbgBULLETe		(0x00000080)	// EnemyBulletStatus
//#define dbg		(0x00000000)	// 
//#define dbg		(0x00000000)	// 
//#define dbg		(0x00000000)	// 

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProcess(void);
void UninitDebugProcess(void);
void UpdateDebugProcess(void);
void DrawDebugProcess(void);

void PrintDebugProcess(char *fmt,...);

int GetDebugStatus(int dbgMode);
void OnDebug(int dbgMode);
void OffDebug(int dbgMode);

#endif