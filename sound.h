//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef ___SOUND_INCLUDE_H___
#define ___SOUND_INCLUDE_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum
{	// �T�E���h�ʂ��i���o�[
	BGM_TUTORIAL,
	BGM_TUTORIAL_BACK,
	SOUND_MAX
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT					InitSound(HWND hWnd);	// ������
void					UninitSound(void);		// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound(int no);	// �T�E���h�̃��[�h
void					PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag/* = 0*/);	// �����ƂɍĐ�
void					StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);	// �����ꎞ��~
long					VolumeControl(LPDIRECTSOUNDBUFFER8 pBuffer, LONG volume);	// ���ʃ{�����[���ݒ��ύX����
bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);	// �Đ������ǂ���

#endif