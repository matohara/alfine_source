//=============================================================================
//
// �T�E���h���� <Sound.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef ___SOUND_INCLUDE_H___
#define ___SOUND_INCLUDE_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>


enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};


typedef class DirectSound
{
	static IDirectSound8 *DirectSoundInterface;	// �T�E���h�C���^�[�t�F�[�X

	LPDIRECTSOUNDBUFFER8 SoundBuffer;

public:
	DirectSound();

	static HRESULT Init(HWND hWnd);
	static void    Uninit(void);

	LPDIRECTSOUNDBUFFER8 LoadSound(const char *soundFile);
	void Play(int flag);
	void Stop();
	void Volume(LONG volume);
	bool CheckPlaying();
	void Release();

}DSound;



#endif