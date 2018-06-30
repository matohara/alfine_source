//=============================================================================
//
// デバッグ表示処理 [DebugProcess.cpp]
// Author : 初 景新
//
//=============================================================================
#include "main.h"
#include "DebugProcess.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXFONT	g_pD3DXFont = NULL;			// フォントへのポインタ

unsigned int DebugStatus = 0xFFFFFFFF;	// デバッグ表示の状態

char		g_aStrDebug[1024] = {"\0"};	// デバッグ情報


//=============================================================================
// デバッグ表示処理の初期化
//=============================================================================
HRESULT InitDebugProcess(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// 情報表示用フォントを設定
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// デバッグ表示処理の終了処理
//=============================================================================
void UninitDebugProcess(void)
{
	if(g_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}

//=============================================================================
// デバッグ表示処理の更新処理
//=============================================================================
void UpdateDebugProcess(void)
{

}

//=============================================================================
// デバッグ表示処理の描画処理
//=============================================================================
void DrawDebugProcess(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	//// 情報表示
	//g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0xFF, 0x22, 0x44));

	// 情報表示
	g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0x00, 0x00, 0x00));

	// 情報クリア
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// デバッグ表示の登録
//=============================================================================
void PrintDebugProcess(char *fmt,...)
{
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// 可変引数を処理する為に使用する変数
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, fmt);

	pCur = fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'x':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%x", va_arg(list, int));
				break;

			case 'l':
				pCur++;

				if (*pCur == 'd')
				{
					// 可変引数にアクセスしてその変数を取り出す処理
					sprintf(aWk, "%ld", va_arg(list, long));

				}
				else
				{
					// 可変引数にアクセスしてその変数を取り出す処理
					sprintf(aWk, "%.5lf", va_arg(list, double));
				}
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%.2f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			case 'v':
				{// 可変引数にアクセスしてその変数を取り出す処理
					D3DXVECTOR3 vec = va_arg(list, D3DXVECTOR3);
					sprintf(aWk, "%.2f, %.2f, %.2f", vec.x, vec.y, vec.z);
				}
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);

	// 連結
	if((strlen(g_aStrDebug) + strlen(aBuf)) < sizeof g_aStrDebug - 1)
	{
		strcat(g_aStrDebug, aBuf);
	}
#endif
}

//=============================================================================
// デバッグ表示の状態を操作
//=============================================================================
int GetDebugStatus(int dbgMode)
{
	if (dbgMode != 0)
	{
		return (dbgMode & DebugStatus);
	}

	return DebugStatus;
}

void OnDebug(int dbgMode)
{
	DebugStatus |= dbgMode;
}

void OffDebug(int dbgMode)
{
	DebugStatus &= (~dbgMode);
}
