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
#define TUTORIAL_UI22 "data/�`���[�g���A��/Text22.png"
#define TUTORIAL_UI23 "data/�`���[�g���A��/Text23.png"

#define TUTORIAL_UI31 "data/�`���[�g���A��/poipoi2.png"


/* TutorialObject */
#define TUTORIAL_OBJ01 "data/�`���[�g���A��/obj01.png"

enum TUTORIALSCENE
{
	TS_MOVE,
	TS_SOUSA,
	TS_MOVE2,
	TS_DAMEGE,
	TS_DAMEGEMOVE,
	TS_OKDAMEGE,
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
	
	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// �w�i�|���S��
	BackPolyUI.Init(BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, BACKPOLY_POS_X, BACKPOLY_POS_Y, UI_TEX_BACKPOLY);

	// �I�v�V�������S
	LogoOption.Init(LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGOUI_TEX_BACKPOLY);

	// �X�e�[�W�i���o�[
	NumberSlashMAX.Init(1.0f, 0.0f, 0.0f);

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
#ifndef _DEBUG
	if (PlayerHP == 0)
	{
		PlayerHP = -1;
		CSFade::SetFade(SCENE_RESULT);
	}
#endif // !_DEBUG

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
			CallGuideUI(TestPlayer.GetPosition(0.0f, 46.0f, 10.0f));
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

LPDIRECT3DTEXTURE9 TutorialObjTex = NULL;

C3DPolygonObject TutorialObj[4];
C3DPolygonObject TutorialObjON[8][2];
C3DPolygonObject TutorialObjOF[8][2];

GameSystem GameSys;
PlayerC TestFriend;
C2DUIMenuLogo TutorialUI[2][3];
C2DUIMenuLogo TutorialUIx1[3];
C2DUIMenuLogo TutorialOtete;
TUTORIALSCENE TutorialScene = TS_MOVE;

int Counter = 0;
int RetunPoint = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	D3DXCreateTextureFromFile(GetDevice(), TUTORIAL_OBJ01, &TutorialObjTex);

	// �ϐ��̏�����
	TutorialScene = TS_MOVE;
	Counter = 0;
	RetunPoint = 0;

	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �Q�[��
	GameSys.Init();

	// �I�u�W�F�N�g
	TutorialObj[0].Init(D3DXVECTOR3(200.0f, 50.0f, -100), 50, 50);
	TutorialObj[1].Init(D3DXVECTOR3(155.0f, 50.0f, -50), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50);
	TutorialObj[2].Init(D3DXVECTOR3(-450.0f, 50.0f, -100), 50, 50);
	TutorialObj[3].Init(D3DXVECTOR3(-495.0f, 50.0f, -50), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50);

	int cnt = 0;
	float posX = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		posX = (float)(-1100 + ((GameSys.Notes[cnt].Timing * 3) + 30) + 50);
		if (posX >= 1100)
		{
			posX -= 2200;
		}
		TutorialObjON[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), 50, 50);
		posX -= 45.0f;
		TutorialObjON[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50);
		cnt++;
		
		posX = (float)(-1100 + ((GameSys.Notes[cnt].Timing * 3) + 30) + 50);
		if (posX >= 1100)
		{
			posX -= 2200;
		}
		TutorialObjOF[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), 50, 50);
		posX -= 45.0f;
		TutorialObjOF[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50);
		cnt++;
	}

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
	TutorialUI[1][0].Init(200,  40, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI11);
	TutorialUI[1][1].Init(200,  25, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI12);
	TutorialUI[1][2].Init(300,  15, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI13);
	TutorialUIx1[0].Init( 300, 120, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI21);
	TutorialUIx1[1].Init( 250, 100, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI22);
	TutorialUIx1[2].Init( 250, 100, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI23);
	TutorialOtete.Init(50, 50, RelativeSX(0.35f), 60, TUTORIAL_UI31);

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
		fc = GameSys.Notes[i].Timing - 300;
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

	/* UI */
	TutorialUI[0][0].ReleaseBuffer();
	TutorialUI[0][1].ReleaseBuffer();
	TutorialUI[0][2].ReleaseBuffer();
	TutorialUI[1][0].ReleaseBuffer();
	TutorialUI[1][1].ReleaseBuffer();
	TutorialUI[1][2].ReleaseBuffer();
	TutorialUIx1[0].ReleaseBuffer();
	TutorialUIx1[1].ReleaseBuffer();
	TutorialUIx1[2].ReleaseBuffer();
	TutorialOtete.ReleaseBuffer();

	for (int i = 0; i < 8; i++)
	{
		TutorialObjON[i][0].ReleaseBuffer();
		TutorialObjON[i][1].ReleaseBuffer();
		TutorialObjOF[i][0].ReleaseBuffer();
		TutorialObjOF[i][1].ReleaseBuffer();
	}


	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �Q�[��
	GameSys.Uninit();

	// �I�u�W�F�N�g
	TutorialObj[0].ReleaseBuffer();
	TutorialObj[1].ReleaseBuffer();

	TutorialObj[2].ReleaseBuffer();
	TutorialObj[3].ReleaseBuffer();

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
		else if (GameSys.TestPlayer.GetPosition().x <= -600.0f)
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
			Counter = 0;
		}
	}
		break;
	case TS_SOUSA:
	{
		if (Counter < 150)
		{
			Counter++;
			TutorialUI[0][0].Open01();	// �X�y�[�X�ŕς���
			if ((GetKeyboardTrigger(DIK_RETURN))|| (IsButtonTriggered(0, BUTTON_X)))
			{
				Counter = 150;
			}
		}
		else if (Counter == 150)
		{
			TutorialUI[0][0].Close01();
			if ((GetKeyboardTrigger(DIK_SPACE)) || (IsButtonTriggered(0, BUTTON_X)))// �ω��𔻒�
			{
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
				CSFade::SetFade(0.2f);
				Counter = 160;
			}
		}
		else if (Counter == 160)
		{
			TutorialUIx1[0].Open01();
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))// �ω��𔻒�
			{
				Counter = 200;
			}
		}
		else if (Counter < 400)
		{
			TutorialUIx1[0].Close01();
			Counter++;
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x + 40);
		}
		else if (Counter == 400)
		{
			if ((GetKeyboardTrigger(DIK_SPACE)) || (IsButtonTriggered(0, BUTTON_X)))
			{
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
				CSFade::SetFade(0.2f);
				TutorialScene = TS_MOVE2;
				Counter = 0;
			}
		}
	}
		break;
	case TS_MOVE2:
	{
		Counter++;
		if (Counter >= 60)
		{
			if (GameSys.TestPlayer.GetPosition().x <= 0.0f)
			{
				// �v���C���[
				GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
				GameSys.TestPlayer.Animation();
				TestFriend.Update(GameSys.TestPlayer.GetPosition().x + 40);
			}
			else
			{
				TutorialScene = TS_DAMEGE;
				Counter = 0;
			}
		}
	}
		break;
	case TS_DAMEGE:
		Counter++;
		TutorialUI[0][1].Open01();	// �_���[�W�󂯂��Ⴄ��
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			TutorialScene = TS_DAMEGEMOVE;
			Counter = 0;
		}
		break;
	case TS_DAMEGEMOVE: //���ۂɃ_���[�W���󂯂Ă݂�
	{
		if (Counter <= 80)
		{
			Counter++;
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
		}
		else
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);

			if (TutorialObj[0].HitCheck(GameSys.TestPlayer.GetPosition() + D3DXVECTOR3(80.0f, 0.0f, 0.0f)))
			{
				GameSys.PlayerHP--;
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
				CSFade::SetFade(0.2f, GAMECOLOR_RED);
				TutorialScene = TS_OKDAMEGE;
				Counter = 0;
			}
		}
	}
		break;
	case TS_OKDAMEGE:
	{
		if (Counter < 300)
		{
			Counter++;
			if (Counter % 30 == 0)
			{
				TutorialOtete.Animation03();
			}
		}
		else if (Counter <= 300)
		{
			TutorialUIx1[1].Open01();
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
			{
				Counter = 400;
			}
		}
		else if (Counter == 400)
		{
			TutorialUIx1[2].Open01();
			if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
			{
				Counter = 450;
			}
		}
		else if (GameSys.TestPlayer.GetPosition().x <= 400)
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);
			Counter = 500;
		}
		else if (Counter == 500)
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			CSFade::SetFade(0.2f);
			Counter = 600;
		}
		else if (GameSys.TestPlayer.GetPosition().x <= 700)
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);
		}
		else if (Counter == 600)
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			CSFade::SetFade(0.2f);
			Counter = 700;
		}
		else if (GameSys.TestPlayer.GetPosition().x <= 900)
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);
		}
		else if (Counter == 700)
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			CSFade::SetFade(0.2f);
			Counter = 800;
		}
		else if (GameSys.TestPlayer.GetPosition().x < 1100)
		{
			// �v���C���[
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);
		}
		else
		{
			GameSys.TestPlayer.SetMapNumber(1);
			GameSys.TestPlayer.SetPositionX(-1100);
			CSFade::SetFade(0.2f);
			TutorialScene = TS_TOPLAY;
			Counter = 0;
		}
	}
		break;
	case TS_TOPLAY:
		Counter++;
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			TutorialScene = TS_PLAYING;
			Counter = 0;
			GameSys.GameFlag |= FLAG_GAME_PLAYING;
			GameSys.PlayerHP = 5;
		}
		TutorialUI[0][2].Open01();
		break;
	case TS_PLAYING:
		if (!Counter)
		{
			Counter = 1;
			// �Đ�
			PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
			PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
		}

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
	if (TutorialScene == TS_PLAYING)
	{
		if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
		{
			if (GameSys.TestPlayer.GetMapNumber() == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					TutorialObjOF[i][0].Draw(TutorialObjTex);
					TutorialObjOF[i][1].Draw(TutorialObjTex);
				}
			}
			else if (GameSys.TestPlayer.GetMapNumber() == 2)
			{
				for (int i = 4; i < 8; i++)
				{
					TutorialObjOF[i][0].Draw(TutorialObjTex);
					TutorialObjOF[i][1].Draw(TutorialObjTex);
				}
			}
		}
		else
		{
			if (GameSys.TestPlayer.GetMapNumber() == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					TutorialObjON[i][0].Draw(TutorialObjTex);
					TutorialObjON[i][1].Draw(TutorialObjTex);
				}
			}
			else if (GameSys.TestPlayer.GetMapNumber() == 2)
			{
				for (int i = 4; i < 8; i++)
				{
					TutorialObjON[i][0].Draw(TutorialObjTex);
					TutorialObjON[i][1].Draw(TutorialObjTex);
				}
			}
		}
	}
	else
	{
		if (!SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
		{
			TutorialObj[0].Draw(TutorialObjTex);
			TutorialObj[1].Draw(TutorialObjTex);

			TutorialObj[2].Draw(TutorialObjTex);
			TutorialObj[3].Draw(TutorialObjTex);
		}
	}

	// �Q�[��
	GameSys.Draw();

	// �F�l
	TestFriend.Draw();

	switch (TutorialScene)
	{
	case TS_SOUSA:
		if ((Counter == 150) || (Counter == 400))
			TutorialUI[1][0].Draw();// ��
		if (Counter <= 170)
			TutorialUI[0][0].Draw();// ��
		if (Counter >= 160)
			TutorialUIx1[0].Draw();
		break;
	case TS_MOVE2:
		if (Counter == 0)
			TutorialUIx1[0].Draw();
		break;
	case TS_DAMEGE:
		if (Counter >= 150)
			TutorialUI[1][1].Draw();
		else
			TutorialUI[0][1].Draw();
		break;
	case TS_DAMEGEMOVE: //���ۂɃ_���[�W���󂯂Ă݂�
		break;
	case TS_OKDAMEGE:
		if (Counter <= 300)
			TutorialOtete.Draw();
		if (Counter > 0 && Counter <= 300)
			TutorialUIx1[1].Draw();
		else if (Counter == 400)
			TutorialUIx1[2].Draw();
		break;
	case TS_TOPLAY:
		if (Counter >= 150)
			TutorialUI[1][2].Draw();
		else
			TutorialUI[0][2].Draw();
		break;
	case TS_PLAYING:
		break;
	}

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

