//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 初 景新
//
//=============================================================================
#ifndef ___SOUND_INCLUDE_H___
#define ___SOUND_INCLUDE_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum
{	// サウンド通しナンバー
	BGM_TUTORIAL,
	BGM_TUTORIAL_BACK,
	SOUND_MAX
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT					InitSound(HWND hWnd);	// 初期化
void					UninitSound(void);		// 後片付け
LPDIRECTSOUNDBUFFER8	LoadSound(int no);	// サウンドのロード
void					PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag/* = 0*/);	// 音ごとに再生
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);	// 音を一時停止
long					VolumeControl(LPDIRECTSOUNDBUFFER8 pBuffer, LONG volume);	// 音量ボリューム設定を変更する
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);	// 再生中かどうか

#endif