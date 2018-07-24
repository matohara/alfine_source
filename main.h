//=============================================================================
//
// ���C������ [main.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS		// warning�h�~

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include <dinput.h>			// DirectInput�֘A�̃w�b�_�[
#include <xaudio2.h>		// XAudio2�֘A�̃w�b�_�[

#include "Library\DebugProcess.h"


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1024)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(576)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����


/* �}�N���֐� */
#define RelativeSX(m) (SCREEN_WIDTH * m)
#define RelativeSY(m) (SCREEN_HEIGHT * m)


/* ��p�}�N�� */
#define DXV2(x, y)    D3DXVECTOR2(x, y);
#define DXV3(x, y, z) D3DXVECTOR3(x, y, z)


/* �Q�[����Ԃ̎�� */
typedef enum
{
	SCENE_TITLE = 0,	// �^�C�g�����
	SCENE_STAGESELECT,	// �X�e�[�W�I�����
	SCENE_TUTORIAL,		// �`���[�g���A��
	SCENE_GAME,			// ���C���Q�[��
	SCENE_RESULT,		// ���U���g���
	SCENE_PAUSE,		// �|�[�Y���
	SCENE_MAX,
	SCENE_END,	// �A�v���I��
} GAMESCENE;


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 normal;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

GAMESCENE SetGameScene(GAMESCENE scene);

HWND GethWnd(void);


#endif