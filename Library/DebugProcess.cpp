//=============================================================================
//
// �f�o�b�O�\������ [DebugProcess.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "DebugProcess.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXFONT	g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^

unsigned int DebugStatus = 0xFFFFFFFF;	// �f�o�b�O�\���̏��

char		g_aStrDebug[1024] = {"\0"};	// �f�o�b�O���


//=============================================================================
// �f�o�b�O�\�������̏�����
//=============================================================================
HRESULT InitDebugProcess(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);

	return hr;
}

//=============================================================================
// �f�o�b�O�\�������̏I������
//=============================================================================
void UninitDebugProcess(void)
{
	if(g_pD3DXFont != NULL)
	{// ���\���p�t�H���g�̊J��
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}

//=============================================================================
// �f�o�b�O�\�������̍X�V����
//=============================================================================
void UpdateDebugProcess(void)
{

}

//=============================================================================
// �f�o�b�O�\�������̕`�揈��
//=============================================================================
void DrawDebugProcess(void)
{
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	//// ���\��
	//g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0xFF, 0x22, 0x44));

	// ���\��
	g_pD3DXFont->DrawText(NULL, g_aStrDebug, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0x00, 0x00, 0x00));

	// ���N���A
	memset(g_aStrDebug, 0, sizeof g_aStrDebug);
}

//=============================================================================
// �f�o�b�O�\���̓o�^
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
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
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
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'x':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%x", va_arg(list, int));
				break;

			case 'l':
				pCur++;

				if (*pCur == 'd')
				{
					// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
					sprintf(aWk, "%ld", va_arg(list, long));

				}
				else
				{
					// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
					sprintf(aWk, "%.5lf", va_arg(list, double));
				}
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%.2f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			case 'v':
				{// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
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

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

	// �A��
	if((strlen(g_aStrDebug) + strlen(aBuf)) < sizeof g_aStrDebug - 1)
	{
		strcat(g_aStrDebug, aBuf);
	}
#endif
}

//=============================================================================
// �f�o�b�O�\���̏�Ԃ𑀍�
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
