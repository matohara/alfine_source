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
LPD3DXFONT Dx9DebugFont = NULL;			// �t�H���g�ւ̃|�C���^
char       DebugString[1024] = {"\0"};	// �f�o�b�O���


//=============================================================================
// �f�o�b�O�\�������̏�����
//=============================================================================
HRESULT InitDebugProcess(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// ���\���p�t�H���g��ݒ�
	hr = D3DXCreateFont(pDevice,// 3D�f�o�C�X
		18,						// �t�H���g�̍���
		 0,						// �t�H���g�̉���
		 0,						// �t�H���g�̑���
		 0,						// �~�j�}�b�v��(1��0�ŏ\��)
		FALSE,					// �C�^���b�N
		SHIFTJIS_CHARSET,		// �t�H���g�^�C�v
		OUT_DEFAULT_PRECIS,		// �uOUT_DEFAULT_PRECIS�v�Œ���ۂ�
		DEFAULT_QUALITY,		// ���ۃt�H���g�ƖړI�t�H���g�̈�v���@���w��
		DEFAULT_PITCH,			// �ς�������ǂӂ��݂�[
		"Terminal",				// �t�H���g�f�[�^��
		&Dx9DebugFont);			// �t�H���g�f�[�^�ۊǏꏊ

	// ���N���A
	memset(DebugString, 0, sizeof DebugString);

	return hr;
}

//=============================================================================
// �f�o�b�O�\�������̏I������
//=============================================================================
void UninitDebugProcess(void)
{
	if(Dx9DebugFont != NULL)
	{// ���\���p�t�H���g�̊J��
		Dx9DebugFont->Release();
		Dx9DebugFont = NULL;
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

	// ���\��
	Dx9DebugFont->DrawText(NULL, DebugString, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xFF, 0xFF, 0x22, 0x44));

	// ���N���A
	memset(DebugString, 0, sizeof DebugString);
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
	if((strlen(DebugString) + strlen(aBuf)) < sizeof DebugString - 1)
	{
		strcat(DebugString, aBuf);
	}
#endif
}

