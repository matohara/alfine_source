//=============================================================================
//
// ステージセレクト処理 [StageSelect.cpp]
// Author : 眞戸原史也
//
//=============================================================================
#include "title.h"
#include "StageSelect.h"
#include "Library\Input.h"
#include "Library\Fade.h"
#include "Library\Sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void BgmStageSelect(int cnt);			// セレクト音楽関数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UIBackGround	StageSelectBack;					// 背景格納変数
Barrel			StageSelectText[SSS_MAX];			// ステージセレクトメッセージ
StageSelectBg	SelectBg[SSS_MAX];					// ステージセレクト背景
Barrel			StageSelectLogo[SSS_MAX];			// ステージセレクト最大数宣言
C2DObject		StageSelectUi;						// ステージセレクトUI

STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;
int 			SSSflag[SSS_MAX];					// バレルフラグ管理変数
int				SELECTflag;							// セレクトフラグ
int				SelectAlpha;						// α値制御変数
bool			UPflag;								// 上移動フラグ
bool			DOWNflag;							// 下移動フラグ

D3DXVECTOR2 selectsize;			// 選択した時のフレームの大きさ
D3DXVECTOR2 flamesize;			// フレームの大きさ
D3DXVECTOR2 selectTexSize;		// 選択した時の文字の大きさ
D3DXVECTOR2 texSize;			// 文字の大きさ
D3DXVECTOR2 speed;				// フレーム移動量

DSound SelectBGM[SSS_MAX];		// セレクトBGM

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStageSelect(void)
{

	// BGM
	SelectBGM[SSS_TUTORIAL].LoadSound("data/BGM/メニュー・チュートリアル.wav");	// チュートリアル
	SelectBGM[SSS_GRASS].LoadSound("data/BGM/メニュー・草原.wav");				// ステージ１
	SelectBGM[SSS_SEASHORE].LoadSound("data/BGM/メニュー・海.wav");				// ステージ２
	SelectBGM[SSS_CRYSTAL].LoadSound("data/BGM/メニュー・水晶.wav");			// ステージ３


	// 背景テクスチャ
	StageSelectBack.LoadTexture(STAGESELECT_TEX_TUTORIAL);

	//フレームサイズの初期化
	selectsize = STAGESELECT_SELECT_SIZE;		// 選択した時のフレームの大きさ
	flamesize = STAGESELECT_FLAME_SIZE;			// フレームの大きさ

	//文字サイズの初期化
	selectTexSize = STAGESELECT_TEX_SELECT_SIZE;	// 選択した時の文字の大きさ
	texSize = STAGESELECT_TEX_SIZE;					// 文字の大きさ


	// 移動量を格納
	speed.x = RelativeSX(FLAME_POS_X_PLUS);
	speed.y = FLAME_POS_Y_PLUS;

	// セレクトフラグを選択中で初期化
	SELECTflag = ROT_SELECT;

	// α値の初期化
	SelectAlpha = BG_BASE_ALPHA;

	// 上移動を未使用で初期化
	UPflag = false;

	// 下移動を使用で初期化
	DOWNflag = true;

	// UIテクスチャ
	StageSelectUi.Init( 320,							// 配置位置X軸
						545,							// 配置位置Y軸
						320,							// テクスチャの横幅
						150,							// テクスチャの縦幅
						STAGESELECT_TEX_UI);			// 読み込むテクスチャ



	// ステージセレクトテクスチャ最大数初期化
	for (int i = 0;i < SSS_MAX;i++)
	{


		// 選択されているフレームだけ拡大
		if (i == SSS_TUTORIAL)
		{

			// 選択されている
			SSSflag[i] = ROT_SELECT;

			// 初起動時はチュートリアルを選択
			SelectBg[i].Init(BG_STAGE_POS_X,				// 配置位置X軸
										SCREEN_CENTER_Y,			// 配置位置Y軸
										BG_STAGE_WIDTH,				// フレームテクスチャの横幅
										BG_STAGE_HEIGHT,			// フレームテクスチャの縦幅
										BG_STAGE_ONE);				// 読み込むテクスチャ

			// 初起動時はチュートリアルを選択
			StageSelectLogo[i].Init(RelativeSX(FLAME_POS_X),		// 配置位置X軸
											   SCREEN_CENTER_Y,				// 配置位置Y軸
											   selectsize.x,				// フレームテクスチャの横幅
											   selectsize.y,				// フレームテクスチャの縦幅
											   STAGESELECT_TEX_FLAME);		// 読み込むテクスチャ

			// 文字テクスチャ
			StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸
												SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// 配置位置Y軸
												selectTexSize.x,						// テクスチャの横幅
												selectTexSize.y,						// テクスチャの縦幅
												STAGESELECT_TEXT_ONE);					// 読み込むテクスチャ

		}

		// それ以外は拡大無し
		else
		{
			// ステージ1
			if (i == SSS_GRASS)
			{
				SelectBg[i].Init(BG_STAGE_POS_X,			// 配置位置X軸
								SCREEN_CENTER_Y,			// 配置位置Y軸
								BG_STAGE_WIDTH,				// フレームテクスチャの横幅
								BG_STAGE_HEIGHT,			// フレームテクスチャの縦幅
								BG_STAGE_TWO);				// 読み込むテクスチャ

															// 文字テクスチャ
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸
										SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// 配置位置Y軸
										texSize.x,						// テクスチャの横幅
										texSize.y,						// テクスチャの縦幅
										STAGESELECT_TEXT_TWO);					// 読み込むテクスチャ


			}

			// ステージ2
			else if (i == SSS_SEASHORE)
			{
				SelectBg[i].Init(BG_STAGE_POS_X,			// 配置位置X軸
								SCREEN_CENTER_Y,			// 配置位置Y軸
								BG_STAGE_WIDTH,				// フレームテクスチャの横幅
								BG_STAGE_HEIGHT,			// フレームテクスチャの縦幅
								BG_STAGE_THREE);			// 読み込むテクスチャ

															// 文字テクスチャ
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸
					SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// 配置位置Y軸
					texSize.x,						// テクスチャの横幅
					texSize.y,						// テクスチャの縦幅
					STAGESELECT_TEXT_THREE);					// 読み込むテクスチャ


			}

			// ステージ3
			else if (i == SSS_CRYSTAL)
			{
				// 初起動時はチュートリアルを選択
				SelectBg[i].Init(BG_STAGE_POS_X,				// 配置位置X軸
								SCREEN_CENTER_Y,				// 配置位置Y軸
								BG_STAGE_WIDTH,					// フレームテクスチャの横幅
								BG_STAGE_HEIGHT,				// フレームテクスチャの縦幅
								BG_STAGE_FOUR);					// 読み込むテクスチャ

																// 文字テクスチャ
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸
					SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// 配置位置Y軸
					texSize.x,						// テクスチャの横幅
					texSize.y,						// テクスチャの縦幅
					STAGESELECT_TEXT_FOUR);					// 読み込むテクスチャ


			}



			// 選択されているフレームより下に
			SSSflag[i] = ROT_DOWN;

			// フレームの初期化
			StageSelectLogo[i].Init(RelativeSX((FLAME_POS_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸 (FLAME_POS_X_PLUS*i)ずれる
									SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),				// 配置位置Y軸 (FLAME_POS_Y_PLUS*i)ずれる
									flamesize.x,										// フレームテクスチャの横幅
									flamesize.y,										// フレームテクスチャの縦幅
									STAGESELECT_TEX_FLAME);								// 読み込むテクスチャ

			// 未選択色
			StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.Release();

	// ステージセレクトUI
	StageSelectUi.Release();


	// ステージセレクト最大数メモリ解放
	for (int i = 0;i < SSS_MAX;i++)
	{

		// ステージセレクトメッセージ
		StageSelectText[i].Release();

		// ステージセレクト背景
		SelectBg[i].Release();

		// ステージセレクト
		StageSelectLogo[i].Release();

		// セレクト音楽
		SelectBGM[i].Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStageSelect(void)
{
	
	// 決定キーを押されたら
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		CSFade::SetFade(SCENE_GAME);
	}

	// ステージセレクト最大数更新処理
	for (int i = 0;i < SSS_MAX;i++)
	{
		// エンターキーを押されたら
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			// ステージセレクト
			switch (SSStastus)
			{
			// チュートリアル
			case SSS_TUTORIAL:

				// 画面遷移:チュートリアル
				CSFade::SetFade(SCENE_GAME);
				break;
			}
		}

		// ↑キーを押したら
		else if ((GetKeyboardTrigger(DIK_UP)) || (IsButtonTriggered(0, LSTICK_UP)))
		{

			// 位置更新用変数を宣言
			D3DXVECTOR2 move;

			// 変数の初期化
			move.x = 0;
			move.y = 0;

			// 上移動可能ならば
			if (UPflag == true)
			{

				// α値の初期化
				SelectAlpha = BG_BASE_ALPHA;

				// 選択フレームより上の場合
				if (SSSflag[i] == ROT_UP)
				{
					// 移動量を更新
					move.x -= speed.x;
					move.y += speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					// セレクトフラグ、または一つ後ろのフラグが選択中だったら
					if ((SELECTflag == ROT_SELECT) || (SSSflag[i + 1] == ROT_SELECT))
					{
						// テクスチャサイズ拡大
						StageSelectLogo[i].LogoSize(selectsize.x, selectsize.y);

						// カラー変更
						StageSelectLogo[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// 文字サイズ拡大
						StageSelectText[i].LogoSize(selectTexSize.x, selectTexSize.y);

						// 文字カラー変更
						StageSelectText[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// フラグを選択フレームへ
						SSSflag[i] = ROT_SELECT;

						// BGM変更
						BgmStageSelect(i);

					}

					else
					{
						// テクスチャ更新
						StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
						StageSelectText[i].LogoSize(texSize.x, texSize.y);		// 文字


					}

					// セレクトフラグをフレーム上へ
					SELECTflag = ROT_UP;
				}

				// 選択フレームより下の場合
				else if (SSSflag[i] == ROT_DOWN)
				{
					// 移動量を更新
					move += speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					// テクスチャ更新
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
					StageSelectText[i].LogoSize(texSize.x,texSize.y);		// 文字


					// セレクトフラグをフレーム下へ
					SELECTflag = ROT_DOWN;
				}

				// 選択されているフレームなら
				else if (SSSflag[i] == ROT_SELECT)
				{

					// 移動量を更新
					move += speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					// テクスチャサイズ縮小
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// 文字

					// カラー変更
					StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// フレーム
					StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// 文字


					// 最後が選択されている場合
					if (i == SSS_CRYSTAL)
					{
						// セレクトフラグを選択中に
						SELECTflag = ROT_DOWN;
					}
					// それ以外
					else
					{
						// セレクトフラグを選択中に
						SELECTflag = ROT_SELECT;
					}

					// フラグを選択フレーム下へ
					SSSflag[i] = ROT_DOWN;

				}
			}
		}

		// ↓キーを押したらz
		else if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
		{

			// 位置更新用変数を宣言
			D3DXVECTOR2 move;

			// 変数の初期化
			move.x = 0;
			move.y = 0;

			// 下移動可能ならば
			if (DOWNflag == true)
			{

				// α値の初期化
				SelectAlpha = BG_BASE_ALPHA;

				// 選択フレームより上の場合
				if (SSSflag[i] == ROT_UP)
				{
					// 移動量を更新
					move.x += speed.x;
					move.y -= speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					// テクスチャ更新
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// 文字

					// セレクトフラグをフレーム上へ
					SELECTflag = ROT_UP;
				}

				// 選択フレームより下の場合
				else if (SSSflag[i] == ROT_DOWN)
				{
					// 移動量を更新
					move -= speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					// セレクトフラグを選択中だったら
					if (SELECTflag == ROT_SELECT)
					{
						// テクスチャサイズ拡大
						StageSelectLogo[i].LogoSize(selectsize.x, selectsize.y);

						// カラー変更
						StageSelectLogo[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// 文字サイズ拡大
						StageSelectText[i].LogoSize(selectTexSize.x, selectTexSize.y);

						// 文字カラー変更
						StageSelectText[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// フラグを選択フレームへ
						SSSflag[i] = ROT_SELECT;

						// BGM変更
						BgmStageSelect(i);

					}

					else
					{
						// テクスチャ更新
						StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
						StageSelectText[i].LogoSize(texSize.x, texSize.y);		// 文字

					}


					// セレクトフラグをフレーム下へ
					SELECTflag = ROT_DOWN;

				}

				// 選択されているフレームなら
				else if (SSSflag[i] == ROT_SELECT)
				{
					// 移動量を更新
					move.x += speed.x;
					move.y -= speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// フレーム
					StageSelectText[i].LogoMove(move.x, move.y);	// 文字

					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// フレーム
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// 文字

					// カラー変更
					StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// フレーム
					StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// 文字

					// セレクトフラグを選択中に
					SELECTflag = ROT_SELECT;

					// フラグを選択フレーム上へ
					SSSflag[i] = ROT_UP;
				}
			}
		}

		// フェード処理
		// 選択背景フェードイン
		SelectBg[i].BgSetAlpha(SelectAlpha);

	}

	// 下移動制御処理
	// 最後の処理だったら
	// ↑キーを押したら
	if ((GetKeyboardTrigger(DIK_UP)) || (IsButtonTriggered(0, LSTICK_UP)))
	{
		// 上移動制御処理
		// 最初の処理だったら
		if (SSSflag[SSS_TUTORIAL] == ROT_SELECT)
		{
			// 上移動制限
			UPflag = false;
		}
		// それ以外
		else
		{
			// 上移動可能
			DOWNflag = true;
		}

	}
	// ↓キーを押したら
	else if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
	{

		if (SSSflag[SSS_CRYSTAL] == ROT_SELECT)
		{
			// 下移動制限
			DOWNflag = false;
		}

		// それ以外
		else
		{
			// 下移動可能
			UPflag = true;
		}
	}

	// α値加算
	// α値が限界値を超えていなければ
	if (SelectAlpha < 255)
	{
		// α値を加算
		SelectAlpha += BG_FADE_SPEED;
	}
	// 超えていたら
	else
	{
		SelectAlpha = 255;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStageSelect(void)
{

	// 背景描画
	StageSelectBack.Draw();

	// ステージセレクト最大数描画処理
	for (int i = 0;i < SSS_MAX;i++)
	{

		// 選択されている場合表示
		if (SSSflag[i] == ROT_SELECT)
		{
			// 選択背景描画
			SelectBg[i].Draw();

		}

		// テクスチャフレーム描画
		StageSelectLogo[i].Draw();

		// 文字描画
		StageSelectText[i].Draw();

	}

	// UI描画
	StageSelectUi.Draw();


}

//=============================================================================
// 音楽選択処理
//=============================================================================
void BgmStageSelect(int cnt)
{

	// ステージセレクト最大数識別
	for (int i = 0;i < SSS_MAX;i++)
	{
		// 選択されてい無いものを止める
		SelectBGM[i].Stop();

		// 選択音楽再生
		if (i == cnt)
		{
			SelectBGM[i].Play(E_DS8_FLAG_LOOP);

		}
	}

}