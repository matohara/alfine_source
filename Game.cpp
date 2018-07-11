//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Game.h"

#include "Library\Input.h"
#include "Library\Sound.h"
#include "Library\Fade.h"
#include "Library\Loading.h"
#include "Library\Light.h"
#include "Camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NOTES_UI_MAX (20)
#define NOTES_FILE  "data/STAGE/Datafile01.txt"

/* TutorialText */
#define TUTORIAL_UI01 "data/�`���[�g���A��/Text00.png"
#define TUTORIAL_UI02 "data/�`���[�g���A��/Text01.png"
#define TUTORIAL_UI03 "data/�`���[�g���A��/Text02.png"
#define TUTORIAL_UI11 "data/�`���[�g���A��/Text10.png"
#define TUTORIAL_UI12 "data/�`���[�g���A��/Text11.png"
#define TUTORIAL_UI13 "data/�`���[�g���A��/Text12.png"

#define TUTORIAL_UI21 "data/�`���[�g���A��/Text21.png"
#define TUTORIAL_UI22 "data/�`���[�g���A��/Text22.png"
#define TUTORIAL_UI23 "data/�`���[�g���A��/Text23.png"

#define TUTORIAL_UI31 "data/�`���[�g���A��/poipoi2.png"


/* TutorialObject */
#define TUTORIAL_OBJ01 "data/�`���[�g���A��/obj01.png"


//*****************************************************************************
// �N���X
//*****************************************************************************

//----������--------
void GameSystem::Init(void)
{
	// ���[�h��ʂ̏�����
	CNowLoading NowLoading;
	NowLoading.Init(SCENE_GAME);

	Notes = NULL;
	GameCounter = 0;
	NotesCounter = 0;
	NotesCounter2 = 3;
	PlayerHP = 5;

	// �K�C�hUI
	GuideUI.Init();

	// �X�e�[�W
	CNotes notes[] = {
		{  160 },
		{  240 },
		{  321 },
		{  403 },
		{  484 },
		{  565 },
		{  642 },
		{  704 },
		{  809 },
		{  883 },
		{  962 },
		{ 1083 },
		{ 1184 },
		{ 1281 },
		{ 1362 },
		{ 1442 } };
	const int notesSize = sizeof(notes) / sizeof(CNotes);
	Notes = new CNotes[notesSize];
	for (int iCnt = 0; iCnt < notesSize; iCnt++)
	{
		Notes[iCnt] = notes[iCnt];
	}

	// �v���C���[
	TestPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	NowLoading.Progress(10);

	// �\�O���
	OnSideBG[0].Init(256, 640, 120, BACK_TEX_ONSIDE_BACK);
	OnSideBG[1].Init(128, 640, 120, BACK_TEX_ONSIDE_FRONT);
	NowLoading.Progress(30);

	// ���O���
	OffSideBG[0].Init(256, 640, 120, BACK_TEX_OFFSIDE_BACK);
	OffSideBG[1].Init(128, 640, 120, BACK_TEX_OFFSIDE_FRONT);
	NowLoading.Progress(60);

	// �t�B�[���h
	OnSideField.Init(480, 270, FIELD_TEX_FRONT);
	OffSideField.Init(480, 270, FIELD_TEX_BACK);
	NowLoading.Progress(90);
	
	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// �w�i�|���S��
	BackPolyUI.Init(BACKPOLY_POS_X, BACKPOLY_POS_Y, BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, UI_TEX_BACKPOLY);

	// �I�v�V�������S
	LogoOption.Init(LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGOUI_TEX_BACKPOLY);

	NowLoading.Progress(100);
	NowLoading.Uninit();
}

//----�I��--------
void GameSystem::Uninit(void)
{
	// �K�C�hUI
	GuideUI.Uninit();

	/* �X�e�[�W */
	delete[] Notes;
	Notes = NULL;

	// �v���C���[
	TestPlayer.Uninit();

	// �O���
	OnSideBG[0].Uninit();
	OnSideBG[1].Uninit();

	OffSideBG[0].Uninit();
	OffSideBG[1].Uninit();

	// �t�B�[���h
	OnSideField.Uninit();
	OffSideField.Uninit();

	/* UI */
	// HP
	HitPointUI.Uninit();

	// �w�i�|���S��
	BackPolyUI.Release();

	// �I�v�V�������S
	LogoOption.Release();
}

//----�X�V--------
void GameSystem::Update(void)
{
	// ���U���g��
#ifndef _DEBUG
	if (PlayerHP == 0)
	{
		PlayerHP = -1;
		CSFade::SetFade(SCENE_RESULT);
	}
#endif // !_DEBUG

	if (GetKeyboardTrigger(DIK_L))
	{
		SetGameFlag(FLAG_GAME_PLAYING, FT_OR);
	}

	if (GameFlag & FLAG_GAME_PLAYING)
	{
		// ����
		if ((GetKeyboardTrigger(DIK_SPACE))||(IsButtonTriggered(0, BUTTON_X)))
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			//if ((GameCounter < Notes[NotesCounter].Timing - 8) ||
			//	(GameCounter > Notes[NotesCounter].Timing + 12))
			//{
			//	CSFade::SetFade(0.2f, GAMECOLOR_RED);
			//	PlayerHP--;
			//}
			//else
			{
				CSFade::SetFade(0.2f);
			}
		}

		if (GameCounter == Notes[NotesCounter].Timing - 8)
		{
			CallGuideUI(TestPlayer.GetPosition() + D3DXVECTOR3(0.0f, 46.0f, 10.0f));
		}
		if (GameCounter == Notes[NotesCounter].Timing + 12)
		{
			if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) != SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
			{
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);	// ���݂̕\��������X�V
				PlayerHP--;
				CSFade::SetFade(0.4f, GAMECOLOR_RED);
			}
			SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHANGE);	// ���̕\��������X�V
			NotesCounter++;
		}

#ifdef _DEBUG
		// UI
		if (GameCounter == Notes[NotesCounter2].Timing - 300)
		{
			CallNotesUI();
			NotesCounter2++;
			if (NotesCounter2 >= 64)
			{
				NotesCounter2 = 64;
			}
		}
#endif // _DEBUG


		// �Q�[����i�s
		GameCounter++;

		// �v���C���[
		if (TestPlayer.Update())
		{
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
			SetGameScene(SCENE_RESULT);
		}

		// �O���&�t�B�[���h


		// �K�C�hUI
		if (GuideUI.Active)
		{
			GuideUI.Update();
		}
	}

	/* UI */
	// HP
	HitPointUI.Update();

	// �w�i�|���S��

	// �I�v�V�������S

	// �f�o�b�O
	if (SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
	{
		PrintDebugProcess("���݂͕\�̂͂��ł�\n");
	}
	else
	{
		PrintDebugProcess("���݂͗��̂͂��ł�\n");
	}
	PrintDebugProcess("�Q�[���^�C�}�[ : %d\n", GameCounter);

}

//----�`��--------
void GameSystem::Draw(void)
{
	// �K�C�hUI
	if (GuideUI.Active)
	{
		GuideUI.Draw();
	}

	/* �X�e�[�W */
	// �v���C���[
	TestPlayer.Draw();

	// �O���&�t�B�[���h
	if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
	{
		OffSideBG[0].Draw();
		OffSideBG[1].Draw();
		OffSideField.Draw();
	}
	else
	{
		OnSideBG[0].Draw();
		OnSideBG[1].Draw();
		OnSideField.Draw();
	}

	/* UI */
	// HP
	HitPointUI.Draw(PlayerHP);

	// �w�i�|���S��
	BackPolyUI.Draw();

	// �I�v�V�������S
	LogoOption.Draw();

}

//----GuideUI�Ăяo��--------
void GameSystem::CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTSOUNDBUFFER8 g_pBGM[2]; // BGM�p�o�b�t�@

#ifdef _DEBUG
UICNotesLane NotesLane;
UICNotes UINotes[NOTES_UI_MAX];
#endif // DEBUG

LPDIRECT3DTEXTURE9 TutorialObjTex = NULL;
C3DPolygonObject TutorialObjON[8][2];
C3DPolygonObject TutorialObjOF[8][2];

GameSystem GameSys;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �I�u�W�F�N�g
	D3DXCreateTextureFromFile(GetDevice(), TUTORIAL_OBJ01, &TutorialObjTex);
	if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
	{
		for (int i = 0; i < 8; i++)
		{
			TutorialObjOF[i][0].LoadTexture(TutorialObjTex);
			TutorialObjOF[i][1].LoadTexture(TutorialObjTex);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			TutorialObjON[i][0].LoadTexture(TutorialObjTex);
			TutorialObjON[i][1].LoadTexture(TutorialObjTex);
		}
	}

	// �Q�[��
	GameSys.Init();

	int cnt = 0;
	float posX = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		posX = (float)(GameSys.Notes[cnt].Timing * 3 + 30 + 50);
		TutorialObjON[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), D3DXVECTOR2(50, 50));
		posX -= 45.0f;
		TutorialObjON[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR2(50, 50));
		cnt++;
		
		posX = (float)(GameSys.Notes[cnt].Timing * 3 + 30 + 50);
		TutorialObjOF[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), D3DXVECTOR2(50, 50));
		posX -= 45.0f;
		TutorialObjOF[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR2(50, 50));
		cnt++;
	}

	// ���y���[�h
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

	// GameFlag��������
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

#ifdef _DEBUG
	/* keep */
	// UI�m�[�c���[��
	NotesLane.Init();

	// UI�m�[�c
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Init();
	}

	// UI
	int no = 0;
	int fc = 0;
	for (int i = 0; GameSys.Notes[i].Timing - 300 < 0; i++)
	{
		no = CallNotesUI();
		fc = 300 - GameSys.Notes[i].Timing;
		for (int c = 0; c < fc; c++)
		{
			UINotes[no].Update();
		}
	}
#endif // DEBUG

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	if (TutorialObjTex != NULL)
	{
		TutorialObjTex->Release();
		TutorialObjTex = NULL;
	}

	for (int i = 0; i < 8; i++)
	{
		TutorialObjON[i][0].Release();
		TutorialObjON[i][1].Release();
		TutorialObjOF[i][0].Release();
		TutorialObjOF[i][1].Release();
	}


	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �Q�[��
	GameSys.Uninit();

	// �T�E���h�I������
	StopSound(g_pBGM[0]);
	StopSound(g_pBGM[1]);
	if (g_pBGM[0] != NULL)
	{
		g_pBGM[0]->Release();
		g_pBGM[0] = NULL;
	}
	if (g_pBGM[1] != NULL)
	{
		g_pBGM[1]->Release();
		g_pBGM[1] = NULL;
	}


#ifdef _DEBUG
	/* Keep */
	// UI�m�[�c���[��
	NotesLane.Uninit();

	// UI�m�[�c
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Uninit();
	}
#endif // DEBUG
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	// �J�����X�V
	UpdateCamera(GameSys.TestPlayer.GetPosition());

	// �Q�[��
	GameSys.Update();

#ifdef _DEBUG
	// �Q�[���̍Đ��A��~
	if (GetKeyboardTrigger(DIK_P))
	{
		if (GameSys.GameFlag & FLAG_GAME_PLAYING)
		{
			GameSys.GameFlag &= ~FLAG_GAME_PLAYING;

			StopSound(g_pBGM[0]);
			StopSound(g_pBGM[1]);
		}
		else
		{
			GameSys.GameFlag |= FLAG_GAME_PLAYING;

			// �Đ�
			PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
			PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
		}
	}

	if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
	{
		// ���U���g��
		CSFade::SetFade(SCENE_RESULT);
	}
#endif // _DEBUG

	if (GameSys.GameFlag & FLAG_GAME_PLAYING)
	{
		// �Đ�
		PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
		PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
		VolumeControl(g_pBGM[1], VOLUME_MIN);

		// �T�E���h�X�V
		if (GameSys.GameFlag & FLAG_GAME_MAPSIDES)
		{
			VolumeControl(g_pBGM[0], VOLUME_MIN);
			VolumeControl(g_pBGM[1], VOLUME_MAX);
			PrintDebugProcess("��BGM���t��\n");
		}
		else
		{
			VolumeControl(g_pBGM[0], VOLUME_MAX);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
			PrintDebugProcess("�\BGM���t��\n");
		}

#ifdef _DEBUG
		/* Keep */
		// UI�m�[�c���[��

		// UI�m�[�c
		for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
		{
			if (UINotes[iCnt].Active)
			{
				UINotes[iCnt].Update();
				PrintDebugProcess("�m�[�cUI : No.%d �ғ���\n", iCnt);
			}
		}
#endif // DEBUG
	}

	PrintDebugProcess("���݂̖� : (%d)\n", (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) ? 1 : 0));

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �I�u�W�F�N�g
	if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
	{
		for (int i = 0; i < 8; i++)
		{
			TutorialObjOF[i][0].Draw();
			TutorialObjOF[i][1].Draw();
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			TutorialObjON[i][0].Draw();
			TutorialObjON[i][1].Draw();
		}
	}

	// �Q�[��
	GameSys.Draw();

#ifdef _DEBUG
	/* Keep */
	// UI�m�[�c���[��
	NotesLane.Draw();

	// UI�m�[�c
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		if (UINotes[iCnt].Active)
		{
			UINotes[iCnt].Draw();
		}
	}
#endif // DEBUG

}

//=============================================================================
// GameFlag�擾
//=============================================================================
UINT SetGameFlag(UINT flg, FLAGTYPE type)
{
	switch (type)
	{
	case FT_CHANGE:
		GameSys.GameFlag ^= flg;
		break;
	case FT_OR:
		GameSys.GameFlag |= flg;
		break;
	case FT_DELETE:
		GameSys.GameFlag &= ~flg;
		break;
	case FT_UPDATE:
		GameSys.GameFlag = flg;
		break;
	case FT_CHECK:
		return (GameSys.GameFlag & flg) ? 1 : 0;
	}

	return GameSys.GameFlag;
}

#ifdef _DEBUG
// �Z�b�g�m�[�cUI
int CallNotesUI(void)
{
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		if (UINotes[iCnt].Active == false)
		{
			UINotes[iCnt].Active = true;
			UINotes[iCnt].ReSet();
			return iCnt;
		}
	}
	return -1;
}
#endif // DEBUG

//=============================================================================
// �v���C���[HP
//=============================================================================
int GetPlayerHP(void)
{
	return GameSys.PlayerHP;
}

