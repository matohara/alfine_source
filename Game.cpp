//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Game.h"
#include "Stage.h"

#include "Library\Input.h"
#include "Library\Fade.h"
#include "Library\Loading.h"
#include "Library\Light.h"
#include "Camera.h"
#include "Menu.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NOTES_UI_MAX (20)
#define GAME_TEX_NUMBER "data/TEXTURE/UI/Number.png"


//*****************************************************************************
// �N���X
//*****************************************************************************
DSound         GameSystem::BackMusic[2];
PlayerB        GameSystem::MainPlayer;
CNotes        *GameSystem::Notes;
GameField      GameSystem::OnSideField;
GameField      GameSystem::OffSideField;
GameBackGround GameSystem::OnSideBG[2];
GameBackGround GameSystem::OffSideBG[2];
CountDown      GameSystem::Countdown;
C2DObject      GameSystem::BackPolyUI;
C2DObject      GameSystem::LogoOption;
UICGuide       GameSystem::GuideUI;
UICHitPoint    GameSystem::HitPointUI;
UINT           GameSystem::GameFlag;
int            GameSystem::GameCounter;
int            GameSystem::NotesCounter;
int            GameSystem::NotesCounter2;
int            GameSystem::PlayerHP;

//----������--------
void GameSystem::Init(void)
{
	// ���[�h��ʂ̏�����
	CNowLoading NowLoading;
	NowLoading.Init(SCENE_GAME);

	// �f�[�^�̏�����
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
	MainPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	/* ���[�f�B���O�X�V */
	NowLoading.Progress(10);

	// �\�O���
	OnSideBG[0].Init(256, 640, 120, BACK_TEX_ONSIDE_BACK);
	OnSideBG[1].Init(128, 640, 120, BACK_TEX_ONSIDE_FRONT);
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(30);

	// ���O���
	OffSideBG[0].Init(256, 640, 120, BACK_TEX_OFFSIDE_BACK);
	OffSideBG[1].Init(128, 640, 120, BACK_TEX_OFFSIDE_FRONT);
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(60);

	// �t�B�[���h
	OnSideField.Init(480, 270, FIELD_TEX_FRONT);
	OffSideField.Init(480, 270, FIELD_TEX_BACK);
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(70);
	
	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// �w�i�|���S��
	BackPolyUI.Init(BACKPOLY_POS_X, BACKPOLY_POS_Y, BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, UI_TEX_BACKPOLY);

	// �I�v�V�������S
	LogoOption.Init(LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGOUI_TEX_BACKPOLY);

	// �J�E���g�_�E��
	Countdown.Set(0, 0, 50, 100, GAME_TEX_NUMBER);

	/* ���[�f�B���O�X�V */
	NowLoading.Progress(90);

	// ���j���[
	GameMenu::Init();

	// BGM
	BackMusic[0].LoadSound("data/BGM/tutorial.wav");
	BackMusic[1].LoadSound("data/BGM/tutorialBack.wav");

	/* ���[�f�B���O�X�V&�I�� */
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
	MainPlayer.Uninit();

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

	// �J�E���g�_�E��
	Countdown.Release();

	// ���j���[
	GameMenu::Uninit();

	// BGM
	BackMusic[0].Release();
	BackMusic[1].Release();
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


	// �Q�[���̍Đ��A��~
	if (GetKeyboardTrigger(DIK_ESCAPE))
	{
		if (GameFlag & FLAG_GAME_PLAYING)
		{
			GameFlag &= ~FLAG_GAME_PLAYING;

			BackMusic[0].Stop();
			BackMusic[1].Stop();

			GameMenu::Open();
		}
		else
		{
			GameMenu::Close();
			Countdown.Set(60, 3, 50, 100);
		}
	}

	// �T�E���h�X�V
	if (GameFlag & FLAG_GAME_MAPSIDES)
	{
		BackMusic[0].Volume(VOLUME_MIN);
		BackMusic[1].Volume(VOLUME_MAX);
		PrintDebugProcess("��BGM���t��\n");
	}
	else
	{
		BackMusic[0].Volume(VOLUME_MAX);
		BackMusic[1].Volume(VOLUME_MIN);
		PrintDebugProcess("�\BGM���t��\n");
	}


#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (GetKeyboardPress(DIK_LSHIFT))
		{
			// ���U���g��
			CSFade::SetFade(SCENE_RESULT);
		}
	}
#endif // _DEBUG


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
			CallGuideUI(MainPlayer.GetPosition() + D3DXVECTOR3(0.0f, 46.0f, 10.0f));
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
		if (MainPlayer.Update())
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

	// ���j���[
	if (GameMenu::Update())
	{
		GameMenu::Close();
		Countdown.Set(60, 3, 50, 100);
	}

	// �J�E���g�_�E��
	if (!(GameFlag & FLAG_GAME_PLAYING) && !GameMenu::Check())
	{
		if (Countdown.ActiveCheck())
		{
			Countdown.Animation();
		}
		else
		{
			GameFlag |= FLAG_GAME_PLAYING;

			// �Đ�
			BackMusic[0].Play(E_DS8_FLAG_LOOP);
			BackMusic[1].Play(E_DS8_FLAG_LOOP);
			BackMusic[1].Volume(VOLUME_MIN);
		}
	}

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
	MainPlayer.Draw();

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

	// �J�E���g�_�E��
	if (Countdown.ActiveCheck())
		Countdown.Draw();

	// ���j���[�`��
	GameMenu::Draw();
}

//----GuideUI�Ăяo��--------
void GameSystem::CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#ifdef _DEBUG
UICNotesLane NotesLane;
UICNotes     UINotes[NOTES_UI_MAX];
#endif // DEBUG


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �Q�[��
	GameSystem::Init();

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
	for (int i = 0; GameSystem::Notes[i].Timing - 300 < 0; i++)
	{
		no = CallNotesUI();
		fc = 300 - GameSystem::Notes[i].Timing;
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
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �Q�[��
	GameSystem::Uninit();


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
	UpdateCamera(GameSystem::MainPlayer.GetPosition());

	// �Q�[��
	GameSystem::Update();

#ifdef _DEBUG
	if (GameSystem::GameFlag & FLAG_GAME_PLAYING)
	{
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
	}
#endif // DEBUG

	PrintDebugProcess("���݂̖� : (%d)\n", (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) ? 1 : 0));

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �Q�[��
	GameSystem::Draw();

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
		GameSystem::GameFlag ^= flg;
		break;
	case FT_OR:
		GameSystem::GameFlag |= flg;
		break;
	case FT_DELETE:
		GameSystem::GameFlag &= ~flg;
		break;
	case FT_UPDATE:
		GameSystem::GameFlag = flg;
		break;
	case FT_CHECK:
		return (GameSystem::GameFlag & flg) ? 1 : 0;
	}

	return GameSystem::GameFlag;
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
	return GameSystem::PlayerHP;
}

