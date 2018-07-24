//=============================================================================
//
// ゲーム画面処理 [Game.cpp]
// Author : 初 景新
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
// マクロ定義
//*****************************************************************************
#define NOTES_UI_MAX (20)
#define GAME_TEX_NUMBER "data/TEXTURE/UI/Number.png"


//*****************************************************************************
// クラス
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

//----初期化--------
void GameSystem::Init(void)
{
	// ロード画面の初期化
	CNowLoading NowLoading;
	NowLoading.Init(SCENE_GAME);

	// データの初期化
	Notes = NULL;
	GameCounter = 0;
	NotesCounter = 0;
	NotesCounter2 = 3;
	PlayerHP = 5;

	// ガイドUI
	GuideUI.Init();

	// ステージ
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

	// プレイヤー
	MainPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	/* ローディング更新 */
	NowLoading.Progress(10);

	// 表前後壁
	OnSideBG[0].Init(256, 640, 120, BACK_TEX_ONSIDE_BACK);
	OnSideBG[1].Init(128, 640, 120, BACK_TEX_ONSIDE_FRONT);
	/* ローディング更新 */
	NowLoading.Progress(30);

	// 裏前後壁
	OffSideBG[0].Init(256, 640, 120, BACK_TEX_OFFSIDE_BACK);
	OffSideBG[1].Init(128, 640, 120, BACK_TEX_OFFSIDE_FRONT);
	/* ローディング更新 */
	NowLoading.Progress(60);

	// フィールド
	OnSideField.Init(480, 270, FIELD_TEX_FRONT);
	OffSideField.Init(480, 270, FIELD_TEX_BACK);
	/* ローディング更新 */
	NowLoading.Progress(70);
	
	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// 背景ポリゴン
	BackPolyUI.Init(BACKPOLY_POS_X, BACKPOLY_POS_Y, BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, UI_TEX_BACKPOLY);

	// オプションロゴ
	LogoOption.Init(LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGOUI_TEX_BACKPOLY);

	// カウントダウン
	Countdown.Set(0, 0, 50, 100, GAME_TEX_NUMBER);

	/* ローディング更新 */
	NowLoading.Progress(90);

	// メニュー
	GameMenu::Init();

	// BGM
	BackMusic[0].LoadSound("data/BGM/tutorial.wav");
	BackMusic[1].LoadSound("data/BGM/tutorialBack.wav");

	/* ローディング更新&終了 */
	NowLoading.Progress(100);
	NowLoading.Uninit();
}

//----終了--------
void GameSystem::Uninit(void)
{
	// ガイドUI
	GuideUI.Uninit();

	/* ステージ */
	delete[] Notes;
	Notes = NULL;

	// プレイヤー
	MainPlayer.Uninit();

	// 前後壁
	OnSideBG[0].Uninit();
	OnSideBG[1].Uninit();

	OffSideBG[0].Uninit();
	OffSideBG[1].Uninit();

	// フィールド
	OnSideField.Uninit();
	OffSideField.Uninit();

	/* UI */
	// HP
	HitPointUI.Uninit();

	// 背景ポリゴン
	BackPolyUI.Release();

	// オプションロゴ
	LogoOption.Release();

	// カウントダウン
	Countdown.Release();

	// メニュー
	GameMenu::Uninit();

	// BGM
	BackMusic[0].Release();
	BackMusic[1].Release();
}

//----更新--------
void GameSystem::Update(void)
{
	// リザルトへ
#ifndef _DEBUG
	if (PlayerHP == 0)
	{
		PlayerHP = -1;
		CSFade::SetFade(SCENE_RESULT);
	}
#endif // !_DEBUG


	// ゲームの再生、停止
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

	// サウンド更新
	if (GameFlag & FLAG_GAME_MAPSIDES)
	{
		BackMusic[0].Volume(VOLUME_MIN);
		BackMusic[1].Volume(VOLUME_MAX);
		PrintDebugProcess("裏BGM演奏中\n");
	}
	else
	{
		BackMusic[0].Volume(VOLUME_MAX);
		BackMusic[1].Volume(VOLUME_MIN);
		PrintDebugProcess("表BGM演奏中\n");
	}


#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (GetKeyboardPress(DIK_LSHIFT))
		{
			// リザルトへ
			CSFade::SetFade(SCENE_RESULT);
		}
	}
#endif // _DEBUG


	if (GameFlag & FLAG_GAME_PLAYING)
	{
		// 判定
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
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);	// 現在の表裏判定を更新
				PlayerHP--;
				CSFade::SetFade(0.4f, GAMECOLOR_RED);
			}
			SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHANGE);	// 次の表裏判定を更新
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


		// ゲームを進行
		GameCounter++;

		// プレイヤー
		if (MainPlayer.Update())
		{
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
			SetGameScene(SCENE_RESULT);
		}

		// 前後壁&フィールド


		// ガイドUI
		if (GuideUI.Active)
		{
			GuideUI.Update();
		}
	}


	/* UI */
	// HP
	HitPointUI.Update();

	// 背景ポリゴン

	// オプションロゴ

	// メニュー
	if (GameMenu::Update())
	{
		GameMenu::Close();
		Countdown.Set(60, 3, 50, 100);
	}

	// カウントダウン
	if (!(GameFlag & FLAG_GAME_PLAYING) && !GameMenu::Check())
	{
		if (Countdown.ActiveCheck())
		{
			Countdown.Animation();
		}
		else
		{
			GameFlag |= FLAG_GAME_PLAYING;

			// 再生
			BackMusic[0].Play(E_DS8_FLAG_LOOP);
			BackMusic[1].Play(E_DS8_FLAG_LOOP);
			BackMusic[1].Volume(VOLUME_MIN);
		}
	}

	// デバッグ
	if (SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
	{
		PrintDebugProcess("現在は表のはずです\n");
	}
	else
	{
		PrintDebugProcess("現在は裏のはずです\n");
	}
	PrintDebugProcess("ゲームタイマー : %d\n", GameCounter);

}

//----描画--------
void GameSystem::Draw(void)
{
	// ガイドUI
	if (GuideUI.Active)
	{
		GuideUI.Draw();
	}

	/* ステージ */
	// プレイヤー
	MainPlayer.Draw();

	// 前後壁&フィールド
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

	// 背景ポリゴン
	BackPolyUI.Draw();

	// オプションロゴ
	LogoOption.Draw();

	// カウントダウン
	if (Countdown.ActiveCheck())
		Countdown.Draw();

	// メニュー描画
	GameMenu::Draw();
}

//----GuideUI呼び出し--------
void GameSystem::CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}


//*****************************************************************************
// グローバル変数
//*****************************************************************************
#ifdef _DEBUG
UICNotesLane NotesLane;
UICNotes     UINotes[NOTES_UI_MAX];
#endif // DEBUG


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// ゲーム
	GameSystem::Init();

	// GameFlagを初期化
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

#ifdef _DEBUG
	/* keep */
	// UIノーツレーン
	NotesLane.Init();

	// UIノーツ
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
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// ゲーム
	GameSystem::Uninit();


#ifdef _DEBUG
	/* Keep */
	// UIノーツレーン
	NotesLane.Uninit();

	// UIノーツ
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Uninit();
	}
#endif // DEBUG
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	// カメラ更新
	UpdateCamera(GameSystem::MainPlayer.GetPosition());

	// ゲーム
	GameSystem::Update();

#ifdef _DEBUG
	if (GameSystem::GameFlag & FLAG_GAME_PLAYING)
	{
		// UIノーツレーン

		// UIノーツ
		for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
		{
			if (UINotes[iCnt].Active)
			{
				UINotes[iCnt].Update();
				PrintDebugProcess("ノーツUI : No.%d 稼働中\n", iCnt);
			}
		}
	}
#endif // DEBUG

	PrintDebugProcess("現在の面 : (%d)\n", (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) ? 1 : 0));

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// ゲーム
	GameSystem::Draw();

#ifdef _DEBUG
	/* Keep */
	// UIノーツレーン
	NotesLane.Draw();

	// UIノーツ
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
// GameFlag取得
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
// セットノーツUI
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
// プレイヤーHP
//=============================================================================
int GetPlayerHP(void)
{
	return GameSystem::PlayerHP;
}

