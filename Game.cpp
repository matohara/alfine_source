//=============================================================================
//
// ゲーム画面処理 [Game.cpp]
// Author : 初 景新
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
#define TUTORIAL_UI22 "data/チュートリアル/Text22.png"
#define TUTORIAL_UI23 "data/チュートリアル/Text23.png"

#define TUTORIAL_UI31 "data/チュートリアル/poipoi2.png"


/* TutorialObject */
#define TUTORIAL_OBJ01 "data/チュートリアル/obj01.png"


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
	TestPlayer.Init(TEXTURE_PLAYER2, 7, 1);

	NowLoading.Progress(10);

	// 表前後壁
	OnSideBG[0].Init(256, 640, 120, BACK_TEX_ONSIDE_BACK);
	OnSideBG[1].Init(128, 640, 120, BACK_TEX_ONSIDE_FRONT);
	NowLoading.Progress(30);

	// 裏前後壁
	OffSideBG[0].Init(256, 640, 120, BACK_TEX_OFFSIDE_BACK);
	OffSideBG[1].Init(128, 640, 120, BACK_TEX_OFFSIDE_FRONT);
	NowLoading.Progress(60);

	// フィールド
	OnSideField.Init(480, 270, FIELD_TEX_FRONT);
	OffSideField.Init(480, 270, FIELD_TEX_BACK);
	NowLoading.Progress(90);
	
	// HPUI
	HitPointUI.Init(HPUI_MAX_HP);

	// 背景ポリゴン
	BackPolyUI.Init(BACKPOLY_POS_X, BACKPOLY_POS_Y, BACKPOLY_SIZE_X, BACKPOLY_SIZE_Y, UI_TEX_BACKPOLY);

	// オプションロゴ
	LogoOption.Init(LOGO_OPTION_POS_X, LOGO_OPTION_POS_Y, LOGO_OPTION_SIZE_X, LOGO_OPTION_SIZE_Y, LOGOUI_TEX_BACKPOLY);

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
	TestPlayer.Uninit();

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

	if (GetKeyboardTrigger(DIK_L))
	{
		SetGameFlag(FLAG_GAME_PLAYING, FT_OR);
	}

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
			CallGuideUI(TestPlayer.GetPosition() + D3DXVECTOR3(0.0f, 46.0f, 10.0f));
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
		if (TestPlayer.Update())
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
	TestPlayer.Draw();

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

LPDIRECT3DTEXTURE9 TutorialObjTex = NULL;
C3DPolygonObject TutorialObjON[8][2];
C3DPolygonObject TutorialObjOF[8][2];

GameSystem GameSys;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// オブジェクト
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

	// ゲーム
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

	// 音楽ロード
	g_pBGM[0] = LoadSound(BGM_TUTORIAL);
	g_pBGM[1] = LoadSound(BGM_TUTORIAL_BACK);

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
// 終了処理
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


	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// ゲーム
	GameSys.Uninit();

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
	// カメラ更新
	UpdateCamera(GameSys.TestPlayer.GetPosition());

	// ゲーム
	GameSys.Update();

#ifdef _DEBUG
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

	if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
	{
		// リザルトへ
		CSFade::SetFade(SCENE_RESULT);
	}
#endif // _DEBUG

	if (GameSys.GameFlag & FLAG_GAME_PLAYING)
	{
		// 再生
		PlaySound(g_pBGM[0], E_DS8_FLAG_LOOP);
		PlaySound(g_pBGM[1], E_DS8_FLAG_LOOP);
		VolumeControl(g_pBGM[1], VOLUME_MIN);

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

	PrintDebugProcess("現在の面 : (%d)\n", (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK) ? 1 : 0));

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// オブジェクト
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

	// ゲーム
	GameSys.Draw();

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
	return GameSys.PlayerHP;
}

