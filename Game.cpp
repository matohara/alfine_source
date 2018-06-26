//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Game.h"
#include "source/scene/fade.h"
#include "source/scene/Loading.h"

#include "light.h"
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

/* TutorialObject */
#define TUTORIAL_OBJ01 "data/�`���[�g���A��/obj01.png"

enum TUTORIALSCENE
{
	TS_MOVE,
	TS_SOUSA,
	TS_MOVE2,
	TS_DAMEGE,
	TS_TOPLAY,
	TS_PLAYING,
	TS_MAX
};

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
	NotesCounter2 = 0;
	PlayerHP = 5;

	// �K�C�hUI
	GuideUI.Init();

	// �X�e�[�W
	CNotes notes[] = {
		{ 328 },
		{ 408 },
		{ 488 },
		{ 564 },
		{ 647 },
		{ 688 },
		{ 726 },
		{ 805 },
		{ 885 },
		{ 965 },
		{ 1046 },
		{ 1125 },
		{ 1204 },
		{ 1284 },
		{ 1365 },
		{ 1445 },
		{ 1524 },
		{ 1607 },
		{ 1645 },
		{ 1684 },
		{ 1724 },
		{ 1766 },
		{ 1801 },
		{ 1844 },
		{ 1885 },
		{ 1924 },
		{ 2005 },
		{ 2084 },
		{ 2166 },
		{ 2245 },
		{ 2327 },
		{ 2404 },
		{ 2485 },
		{ 2566 },
		{ 2646 },
		{ 2724 },
		{ 2806 },
		{ 2886 },
		{ 2964 },
		{ 3044 },
		{ 3125 },
		{ 3206 },
		{ 3285 },
		{ 3364 },
		{ 3445 },
		{ 3525 },
		{ 3604 },
		{ 3684 },
		{ 3765 },
		{ 3844 },
		{ 3925 } };
	const int notesSize = sizeof(notes) / sizeof(CNotes);
	Notes = new CNotes[notesSize];
	for (int iCnt = 0; iCnt < notesSize; iCnt++)
	{
		Notes[iCnt] = notes[iCnt];
	}

	// �v���C���[
	TestPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	NowLoading.Progress(10);

	// �O���
	BackWall[0].Init(256, 500, 240, TEXTURE_FILE_BACK_B, -1);
	BackWall[1].Init(256, 500, 240, TEXTURE_FILE_BACK_B, 0);
	BackWall[2].Init(256, 500, 240, TEXTURE_FILE_BACK_B, 1);
	NowLoading.Progress(30);

	FrontWall[0].Init(150, 600, 320, TEXTURE_FILE_BACK_F, -1);
	FrontWall[1].Init(150, 600, 320, TEXTURE_FILE_BACK_F, 0);
	FrontWall[2].Init(150, 600, 320, TEXTURE_FILE_BACK_F, 1);
	NowLoading.Progress(60);

	// �t�B�[���h
	TestField[0].Init(512, 256, -1);
	NowLoading.Progress(80);
	TestField[1].Init(512, 256, 0);
	NowLoading.Progress(90);
	TestField[2].Init(512, 256, 1);

	NowLoading.Progress(100);
	NowLoading.Uninit();
	
	Sleep(5000);

	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// �w�i�|���S��
	BackPolyUI.Init(BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, BACKPOLY_POS_X, BACKPOLY_POS_Y, UI_TEX_BACKPOLY);

	// �I�v�V�������S
	LogoOption.Init(LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGOUI_TEX_BACKPOLY);

	// �X�e�[�W�i���o�[
	NumberSlashMAX.Init(1.0f, 0.0f, 0.0f);

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
	BackWall[0].Uninit();
	BackWall[1].Uninit();
	BackWall[2].Uninit();

	FrontWall[0].Uninit();
	FrontWall[1].Uninit();
	FrontWall[2].Uninit();

	// �t�B�[���h
	TestField[0].Uninit();
	TestField[1].Uninit();
	TestField[2].Uninit();

	/* UI */
	// HP
	HitPointUI.Uninit();

	// �w�i�|���S��
	BackPolyUI.ReleaseBuffer();

	// �I�v�V�������S
	LogoOption.ReleaseBuffer();

	// �X�e�[�W�i���o�[
	NumberSlashMAX.Uninit();
}

//----�X�V--------
void GameSystem::Update(void)
{
	// ���U���g��
#if 1
	if (PlayerHP <= 0)
	{
		PlayerHP = 0;
		SetFade(FADE_OUT, SCENE_RESULT);
	}
#endif

	if (GameFlag & FLAG_GAME_PLAYING)
	{
		if (GameCounter > 5400)// 5400 = 90s * 60f
		{
			SetFade(FADE_OUT, SCENE_RESULT);
		}

		// ����
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			if ((GameCounter < Notes[NotesCounter].Timing - 8) ||
				(GameCounter > Notes[NotesCounter].Timing + 12))
			{
				PlayerHP--;
			}
		}

		if (GameCounter == Notes[NotesCounter].Timing - 8)
		{
			CallGuideUI(TestPlayer.GetPosition(0.0f, 46.0f, 10.0f));
		}
		if (GameCounter == Notes[NotesCounter].Timing + 12)
		{
			if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) != SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
			{
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);	// ���݂̕\��������X�V
				PlayerHP--;
			}
			SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHANGE);	// ���̕\��������X�V
			NotesCounter++;
		}

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

		// �Q�[����i�s
		GameCounter++;

		// �v���C���[
		if (TestPlayer.Update())
		{
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
			SetGameScene(SCENE_RESULT);
		}

		// �O���
		//BackWall[0].Update();
		//BackWall[1].Update();
		//BackWall[2].Update();
		//FrontWall[0].Update();
		//FrontWall[1].Update();
		//FrontWall[2].Update();

		// �t�B�[���h
		//TestField[0].Update();
		//TestField[1].Update();
		//TestField[2].Update();

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

	// �X�e�[�W�i���o�[
	NumberSlashMAX.Update(TestPlayer.GetMapNumber() + 1);

	// �f�o�b�O
	if (SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
	{
		PrintDebugProcess("���݂͕\�ł�\n");
	}
	else
	{
		PrintDebugProcess("���݂͗��ł�\n");
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

	// �O���
	BackWall[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	BackWall[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	BackWall[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());

	FrontWall[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	FrontWall[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	FrontWall[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());

	// �t�B�[���h
	TestField[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	TestField[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	TestField[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());


	/* UI */
	// HP
	HitPointUI.Draw(PlayerHP);

	// �w�i�|���S��
	BackPolyUI.Draw();

	// �I�v�V�������S
	LogoOption.Draw();

	// �X�e�[�W�i���o�[
	NumberSlashMAX.Draw();

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

C3DPolygonObject TutorialObj[2];

GameSystem GameSys;
PlayerC TestFriend;
C2DUIMenuLogo TutorialUI[2][3];
C2DUIMenuLogo TutorialUIx1[2];
TUTORIALSCENE TutorialScene = TS_MOVE;

int Couner = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{

	// �ϐ��̏�����
	TutorialScene = TS_MOVE;
	Couner = 0;

	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �Q�[��
	GameSys.Init();

	// �I�u�W�F�N�g
	TutorialObj[0].Init(D3DXVECTOR3(0.0f, 50.0f, -200), 50, 50, TUTORIAL_OBJ01);
	TutorialObj[1].Init(D3DXVECTOR3(0.0f, 50.0f, -100), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50, TUTORIAL_OBJ01);

	// �F�l
	TestFriend.Init(TEXTURE_FRIEND2, 7, 1);
	TestFriend.FlipX();

	// ���y���[�h
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

	// GameFlag��������
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

	/* UI */
	// �`���[�g���A��
	TutorialUI[0][0].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI01);
	TutorialUI[0][1].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI02);
	TutorialUI[0][2].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI03);
	TutorialUI[1][0].Init(300,  60, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI11);
	TutorialUI[1][1].Init(320,  40, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI12);
	TutorialUI[1][2].Init(300,  15, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI13);
	TutorialUIx1[0].Init( 300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI21);

#ifdef _DEBUG
	/* keep */
	// UI�m�[�c���[��
	NotesLane.Init();

	// UI�m�[�c
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Init();
	}
#endif // DEBUG

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	/* UI */
	TutorialUI[0][0].ReleaseBuffer();
	TutorialUI[0][1].ReleaseBuffer();
	TutorialUI[0][2].ReleaseBuffer();
	TutorialUI[1][0].ReleaseBuffer();
	TutorialUI[1][1].ReleaseBuffer();
	TutorialUI[1][2].ReleaseBuffer();
	TutorialUIx1[0].ReleaseBuffer();

	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �Q�[��
	GameSys.Uninit();

	// �I�u�W�F�N�g
	TutorialObj[0].ReleaseBuffer();

	// �F�l
	TestFriend.Uninit();

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

	// ����
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
	//}

	// �J�����X�V
	UpdateCamera(GameSys.TestPlayer.GetPosition());

	// �Q�[��
	GameSys.Update();


	switch (TutorialScene)
	{
	case TS_MOVE:
	{
		if (GameSys.TestPlayer.GetPosition().x <= -800.0f)
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			// �F�l
			TestFriend.SetPosition(-760.0f);
		}
		else if (GameSys.TestPlayer.GetPosition().x <= -400.0f)
		{
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x + 40);
		}
		else
		{
			TutorialScene = TS_SOUSA;
			GameSys.TestPlayer.ReSetTexture();
			TestFriend.ReSetTexture();
		}
	}
		break;
	case TS_SOUSA:
	{
		Couner++;
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Couner = 150;
		}
		TutorialUI[0][0].Open01();

		if (Couner >= 150)
		{
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				TutorialScene = TS_MOVE2;
				Couner = 0;
			}
		}
	}
		break;
	case TS_MOVE2:
	{
		TutorialUIx1[0].Open01();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			Couner = 1;
		}

		if (Couner)
		{
			if (GameSys.TestPlayer.GetPosition().x <= -200.0f)
			{
				// �v���C���[
				GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
				GameSys.TestPlayer.Animation();
				TestFriend.Update(GameSys.TestPlayer.GetPosition().x + 40);
			}
			else
			{
				TutorialScene = TS_DAMEGE;
				Couner = 0;
			}
		}
	}
		break;
	case TS_DAMEGE:
		Couner++;
		TutorialUI[0][1].Open01();
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			TutorialScene = TS_TOPLAY;
			Couner = 0;
		}
		break;
	case TS_TOPLAY:
		Couner++;
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			TutorialScene = TS_PLAYING;
			Couner = 0;
		}
		TutorialUI[0][2].Open01();
		break;
	case TS_PLAYING:
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// ���U���g��
			SetFade(FADE_OUT, SCENE_RESULT);
		}

		if (GameSys.GameFlag & FLAG_GAME_PLAYING)
		{
			// �F�l
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);

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

		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �I�u�W�F�N�g
	TutorialObj[0].DrawBillboard();
	TutorialObj[1].Draw();

	// �Q�[��
	GameSys.Draw();

	// �F�l
	TestFriend.Draw();

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

	switch (TutorialScene)
	{
	case TS_SOUSA:
		if (Couner >= 150)
			TutorialUI[1][0].Draw();
		else
			TutorialUI[0][0].Draw();
		break;
	case TS_MOVE2:
		if (Couner == 0)
			TutorialUIx1[0].Draw();
		break;
	case TS_DAMEGE:
		if (Couner >= 150)
			TutorialUI[1][1].Draw();
		else
			TutorialUI[0][1].Draw();
		break;
	case TS_TOPLAY:
		if (Couner >= 150)
			TutorialUI[1][2].Draw();
		else
			TutorialUI[0][2].Draw();
		break;
	case TS_PLAYING:
		break;
	}

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
//=============================================================================
// �Z�b�g�m�[�cUI
//=============================================================================
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

