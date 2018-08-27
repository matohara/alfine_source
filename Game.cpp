//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Game.h"

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
StageBase     *GameSystem::Stage;
DSound         GameSystem::BackMusic[2];
PlayerB        GameSystem::MainPlayer;
SNotes        *GameSystem::Notes;
GameField      GameSystem::OnSideField;
GameField      GameSystem::OffSideField;
GameBackGround GameSystem::OnSideBG;
GameBackGround GameSystem::OffSideBG;
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
	Stage = NULL;
	GameCounter = 0;
	NotesCounter = 0;
	NotesCounter2 = 3;
	PlayerHP = 5;

	// �K�C�hUI
	GuideUI.Init();

	// �X�e�[�W
	Stage = GetRunStage();
	Stage->Init();

	// �v���C���[
	MainPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	/* ���[�f�B���O�X�V */
	NowLoading.Progress(10);

	// �X�e�[�W������
	Stage->back_Init();
	Stage->Init();
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(20);

	// �\�O���
	OnSideBG.Init(256, 640, 120, Stage->BackTexOn.c_str());
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(30);

	// ���O���
	OffSideBG.Init(256, 640, 120, Stage->BackTexOff.c_str());
	/* ���[�f�B���O�X�V */
	NowLoading.Progress(40);

	// �t�B�[���h
	OnSideField.Init(480, 270, Stage->FieldTexOn.c_str());
	OffSideField.Init(480, 270, Stage->FieldTexOff.c_str());
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
	BackMusic[0].LoadSound(Stage->MusicPassOn.c_str());
	BackMusic[1].LoadSound(Stage->MusicPassOff.c_str());

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
	OnSideBG.Uninit();
	OffSideBG.Uninit();

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

	// �X�e�[�W
	Stage->back_Uninit();
	delete Stage;
	Stage = NULL;
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

	// �X�e�[�W
	Stage->Update();

	// �|�[�Y
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

	/* �v���C������ */
	if (GameFlag & FLAG_GAME_PLAYING)
	{
		// ����
		if ((GetKeyboardTrigger(DIK_SPACE)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
			CSFade::SetFade(0.2f);
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

		// �K�C�hUI
		if (GuideUI.CheckActive())
		{
			GuideUI.Update();
		}
	}

	// ���j���[
	if (GameMenu::Update())
	{
		GameMenu::Close();
		Countdown.Set(60, 3, 50, 100);
	}

	// �J�E���g�_�E��
	if (~GameFlag & FLAG_GAME_PLAYING && !GameMenu::Check())
	{
		if (Countdown.ActiveCheck())
		{
			Countdown.Animation();
		}
		else
		{
			GameFlag |= FLAG_GAME_PLAYING;

			// �Đ�
			BackMusic[0].Play(E_DS8_FLAG_NONE);
			BackMusic[1].Play(E_DS8_FLAG_NONE);
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
	if (GuideUI.CheckActive())
	{
		GuideUI.Draw();
	}

	/* �X�e�[�W */
	Stage->back_Draw(SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK));
	Stage->Draw();

	// �v���C���[
	MainPlayer.Draw();

	// �O���&�t�B�[���h
	if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
	{
		OffSideBG.Draw();
		OffSideField.Draw();
	}
	else
	{
		OnSideBG.Draw();
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
	NotesLane.Release();

	// UI�m�[�c
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Release();
	}
#endif // DEBUG
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	D3DXVECTOR3 playerVec = GameSystem::MainPlayer.GetPosition();
	// �J�����X�V
	UpdateCamera(playerVec);

	// �Q�[��
	if (playerVec.x < 0.0f)
	{
		GameSystem::MainPlayer.Move(DXV3(2.0f, 0.0f, 0.0f));
	}
	else if (playerVec.x >= -2.0f && playerVec.x <= 0.0f)
	{
		GameSystem::MainPlayer.SetPositionX(0.01f);
		GameSystem::Countdown.Set(60, 3, 50, 100);
	}
	else
	{
		GameSystem::Update();
	}

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

	PrintDebugProcess("�v���C���[�ʒu : (%v)\n", playerVec);

	PrintDebugProcess("���݂̖� : (%d)\n", (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) ? 1 : 0));
	PrintDebugProcess("�Q�[����Run��� : %d", SetGameFlag(FLAG_GAME_PLAYING, FT_CHECK) ? 1 : 0);
#endif // DEBUG

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

