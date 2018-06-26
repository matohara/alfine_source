//=============================================================================
//
// ゲーム画面処理 [Game.cpp]
// Author : 初 景新
//
//=============================================================================
#include "Game.h"
#include "source/scene/fade.h"
#include "source/scene/Loading.h"

#include "light.h"
#include "Camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NOTES_UI_MAX (20)
#define NOTES_FILE  "data/STAGE/Datafile01.txt"

/* TutorialText */
#define TUTORIAL_UI01 "data/チュートリアル/Text00.png"
#define TUTORIAL_UI02 "data/チュートリアル/Text01.png"
#define TUTORIAL_UI03 "data/チュートリアル/Text02.png"
#define TUTORIAL_UI11 "data/チュートリアル/Text10.png"
#define TUTORIAL_UI12 "data/チュートリアル/Text11.png"
#define TUTORIAL_UI13 "data/チュートリアル/Text12.png"

#define TUTORIAL_UI21 "data/チュートリアル/Text21.png"

/* TutorialObject */
#define TUTORIAL_OBJ01 "data/チュートリアル/obj01.png"

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
// クラス
//*****************************************************************************

//----初期化--------
void GameSystem::Init(void)
{
	// ロード画面の初期化
	CNowLoading NowLoading;
	NowLoading.Init(SCENE_GAME);

	Notes = NULL;
	GameCounter = 0;
	NotesCounter = 0;
	NotesCounter2 = 0;
	PlayerHP = 5;

	// ガイドUI
	GuideUI.Init();

	// ステージ
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

	// プレイヤー
	TestPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	NowLoading.Progress(10);

	// 前後壁
	BackWall[0].Init(256, 500, 240, TEXTURE_FILE_BACK_B, -1);
	BackWall[1].Init(256, 500, 240, TEXTURE_FILE_BACK_B, 0);
	BackWall[2].Init(256, 500, 240, TEXTURE_FILE_BACK_B, 1);
	NowLoading.Progress(30);

	FrontWall[0].Init(150, 600, 320, TEXTURE_FILE_BACK_F, -1);
	FrontWall[1].Init(150, 600, 320, TEXTURE_FILE_BACK_F, 0);
	FrontWall[2].Init(150, 600, 320, TEXTURE_FILE_BACK_F, 1);
	NowLoading.Progress(60);

	// フィールド
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

	// 背景ポリゴン
	BackPolyUI.Init(BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, BACKPOLY_POS_X, BACKPOLY_POS_Y, UI_TEX_BACKPOLY);

	// オプションロゴ
	LogoOption.Init(LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGOUI_TEX_BACKPOLY);

	// ステージナンバー
	NumberSlashMAX.Init(1.0f, 0.0f, 0.0f);

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
	TestPlayer.Uninit();

	// 前後壁
	BackWall[0].Uninit();
	BackWall[1].Uninit();
	BackWall[2].Uninit();

	FrontWall[0].Uninit();
	FrontWall[1].Uninit();
	FrontWall[2].Uninit();

	// フィールド
	TestField[0].Uninit();
	TestField[1].Uninit();
	TestField[2].Uninit();

	/* UI */
	// HP
	HitPointUI.Uninit();

	// 背景ポリゴン
	BackPolyUI.ReleaseBuffer();

	// オプションロゴ
	LogoOption.ReleaseBuffer();

	// ステージナンバー
	NumberSlashMAX.Uninit();
}

//----更新--------
void GameSystem::Update(void)
{
	// リザルトへ
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

		// 判定
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
				SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);	// 現在の表裏判定を更新
				PlayerHP--;
			}
			SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHANGE);	// 次の表裏判定を更新
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

		// ゲームを進行
		GameCounter++;

		// プレイヤー
		if (TestPlayer.Update())
		{
			SetGameFlag(FLAG_GAME_PLAYING, FT_DELETE);
			SetGameScene(SCENE_RESULT);
		}

		// 前後壁
		//BackWall[0].Update();
		//BackWall[1].Update();
		//BackWall[2].Update();
		//FrontWall[0].Update();
		//FrontWall[1].Update();
		//FrontWall[2].Update();

		// フィールド
		//TestField[0].Update();
		//TestField[1].Update();
		//TestField[2].Update();

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

	// ステージナンバー
	NumberSlashMAX.Update(TestPlayer.GetMapNumber() + 1);

	// デバッグ
	if (SetGameFlag(FLAG_GAME_NEXTSIDES, FT_CHECK))
	{
		PrintDebugProcess("現在は表です\n");
	}
	else
	{
		PrintDebugProcess("現在は裏です\n");
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
	TestPlayer.Draw();

	// 前後壁
	BackWall[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	BackWall[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	BackWall[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());

	FrontWall[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	FrontWall[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	FrontWall[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());

	// フィールド
	TestField[0].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	TestField[1].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());
	TestField[2].Draw((int)SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK), TestPlayer.GetMapNumber());


	/* UI */
	// HP
	HitPointUI.Draw(PlayerHP);

	// 背景ポリゴン
	BackPolyUI.Draw();

	// オプションロゴ
	LogoOption.Draw();

	// ステージナンバー
	NumberSlashMAX.Draw();

}

//----GuideUI呼び出し--------
void GameSystem::CallGuideUI(D3DXVECTOR3 pos)
{
	GuideUI.SetGuideUI(pos);
}


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTSOUNDBUFFER8 g_pBGM[2]; // BGM用バッファ

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
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{

	// 変数の初期化
	TutorialScene = TS_MOVE;
	Couner = 0;

	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// ゲーム
	GameSys.Init();

	// オブジェクト
	TutorialObj[0].Init(D3DXVECTOR3(0.0f, 50.0f, -200), 50, 50, TUTORIAL_OBJ01);
	TutorialObj[1].Init(D3DXVECTOR3(0.0f, 50.0f, -100), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 50, 50, TUTORIAL_OBJ01);

	// 友人
	TestFriend.Init(TEXTURE_FRIEND2, 7, 1);
	TestFriend.FlipX();

	// 音楽ロード
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

	// GameFlagを初期化
	SetGameFlag(FLAG_GAME_INIT, FT_UPDATE);

	/* UI */
	// チュートリアル
	TutorialUI[0][0].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI01);
	TutorialUI[0][1].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI02);
	TutorialUI[0][2].Init(300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI03);
	TutorialUI[1][0].Init(300,  60, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI11);
	TutorialUI[1][1].Init(320,  40, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI12);
	TutorialUI[1][2].Init(300,  15, SCREEN_CENTER_X, RelativeSY(0.8f), TUTORIAL_UI13);
	TutorialUIx1[0].Init( 300, 120, SCREEN_CENTER_X, RelativeSY(0.2f), TUTORIAL_UI21);

#ifdef _DEBUG
	/* keep */
	// UIノーツレーン
	NotesLane.Init();

	// UIノーツ
	for (int iCnt = 0; iCnt < NOTES_UI_MAX; iCnt++)
	{
		UINotes[iCnt].Init();
	}
#endif // DEBUG

	return S_OK;
}

//=============================================================================
// 終了処理
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

	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// ゲーム
	GameSys.Uninit();

	// オブジェクト
	TutorialObj[0].ReleaseBuffer();

	// 友人
	TestFriend.Uninit();

	// サウンド終了処理
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
	// ゲームの再生、停止
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

			// 再生
			PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
			PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
			VolumeControl(g_pBGM[1], VOLUME_MIN);
		}
	}

	// 判定
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHANGE);
	//}

	// カメラ更新
	UpdateCamera(GameSys.TestPlayer.GetPosition());

	// ゲーム
	GameSys.Update();


	switch (TutorialScene)
	{
	case TS_MOVE:
	{
		if (GameSys.TestPlayer.GetPosition().x <= -800.0f)
		{
			// プレイヤー
			GameSys.TestPlayer.GoPoint(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			GameSys.TestPlayer.Animation();
			// 友人
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
				// プレイヤー
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
			// リザルトへ
			SetFade(FADE_OUT, SCENE_RESULT);
		}

		if (GameSys.GameFlag & FLAG_GAME_PLAYING)
		{
			// 友人
			TestFriend.Update(GameSys.TestPlayer.GetPosition().x - 40);

			// サウンド更新
			if (GameSys.GameFlag & FLAG_GAME_MAPSIDES)
			{
				VolumeControl(g_pBGM[0], VOLUME_MIN);
				VolumeControl(g_pBGM[1], VOLUME_MAX);
				PrintDebugProcess("裏BGM演奏中\n");
			}
			else
			{
				VolumeControl(g_pBGM[0], VOLUME_MAX);
				VolumeControl(g_pBGM[1], VOLUME_MIN);
				PrintDebugProcess("表BGM演奏中\n");
			}

#ifdef _DEBUG
			/* Keep */
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
#endif // DEBUG
		}

		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// オブジェクト
	TutorialObj[0].DrawBillboard();
	TutorialObj[1].Draw();

	// ゲーム
	GameSys.Draw();

	// 友人
	TestFriend.Draw();

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
// GameFlag取得
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
// セットノーツUI
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
// プレイヤーHP
//=============================================================================
int GetPlayerHP(void)
{
	return GameSys.PlayerHP;
}

