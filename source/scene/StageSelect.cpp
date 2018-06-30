//=============================================================================
//
// ステージセレクト処理 [StageSelect.cpp]
// Author : 眞戸原史也
//
//=============================================================================
#include "title.h"
#include "../../input.h"
#include "fade.h"
#include "../../DebugProcess.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/Tutorial.jpg"
#define STAGESELECT_TEX_TUTORIAL_LOGO "data/TEXTURE/STAGEVIEW/TutorialLogo.png"

#define STAGESELECT_TEX_FLAME      "data/TEXTURE/UI/Frame00.png"				// ステージセレクトのフレームテクスチャ
#define STAGESELECT_SELECT_SIZE		D3DXVECTOR2(280.0f, 100.0f)					// 選択した時のテクスチャの大きさ
#define STAGESELECT_FLAME_SIZE		D3DXVECTOR2(240.0f, 60.0f)					// フレームテクスチャの大きさ
#define FLAME_POS_X					(0.7f)										// フレームのx軸配置倍率
#define FLAME_POS_X_PLUS			(0.05f)										// フレームのx軸配置倍率増加値
#define FLAME_POS_Y_PLUS			(120.0f)										// フレームのy軸配置倍率増加値

#define STAGESELECT_TEXT	      "data/TEXTURE/UI/Stage_Tex.png"				// ステージセレクトのフレームテクスチャ

// ステージセレクトマクロ
enum STATUSSTAGESELECT
{
	SSS_TUTORIAL = 0,				// チュートリアル
	SSS_GRASS,						// 草原
	SSS_SEASHORE,					// 海辺
	SSS_CRYSTAL,					// クリスタルの森
	SSS_MAX
};

// バレルセレクトマクロ
enum STATUSSTAGEROT
{
	ROT_DOWN=-1,	// ダウン
	ROT_SELECT,		// セレクト
	ROT_UP,			// アップ
	ROT_MAX			// バレルセレクト最大数
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
C2DUIPolygonA StageSelectBack;
C2DUIMenuLogo StageSelectText;
C2DUIMenuLogo StageSelectLogo[SSS_MAX];				// ステージセレクト最大数宣言
STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;
int 			SSSflag[SSS_MAX];					// バレルフラグ管理変数
int				SELECTflag;							// セレクトフラグ
bool			UPflag;								// 上移動フラグ
bool			DOWNflag;							// 下移動フラグ

D3DXVECTOR2 selectsize;			// 選択した時のフレームの大きさ
D3DXVECTOR2 flamesize;			// フレームの大きさ
D3DXVECTOR2 speed;				// フレーム移動量

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStageSelect(void)
{

	// 背景テクスチャ
	StageSelectBack.Init(STAGESELECT_TEX_TUTORIAL);

	//フレームサイズの初期化
	selectsize = STAGESELECT_SELECT_SIZE;	// 選択した時のフレームの大きさ
	flamesize = STAGESELECT_FLAME_SIZE;		// フレームの大きさ

	// 移動量を格納
	speed.x = RelativeSX(FLAME_POS_X_PLUS);
	speed.y = FLAME_POS_Y_PLUS;

	// セレクトフラグを選択中で初期化
	SELECTflag = ROT_SELECT;

	// 上移動を未使用で初期化
	UPflag = false;

	// 下移動を使用で初期化
	DOWNflag = true;

	// 文字テクスチャ
	StageSelectText.Init(selectsize.x,				// テクスチャの横幅
						selectsize.y+30,				// テクスチャの縦幅
						RelativeSX(FLAME_POS_X),	// 配置位置X軸
						SCREEN_CENTER_Y,			// 配置位置Y軸
						STAGESELECT_TEXT);			// 読み込むテクスチャ

	// ステージセレクトテクスチャ最大数初期化
	for (int i = 0;i < SSS_MAX;i++)
	{

		// 選択されているフレームだけ拡大
		if (i == SSS_TUTORIAL)
		{

			// 選択されている
			SSSflag[i] = ROT_SELECT;

			// 初起動時はチュートリアルを選択
			StageSelectLogo[SSS_TUTORIAL].Init(selectsize.x,				// フレームテクスチャの横幅
											   selectsize.y,				// フレームテクスチャの縦幅
											   RelativeSX(FLAME_POS_X),		// 配置位置X軸
											   SCREEN_CENTER_Y,				// 配置位置Y軸
											   STAGESELECT_TEX_FLAME);		// 読み込むテクスチャ
		}

		// それ以外は拡大無し
		else
		{

			// 選択されているフレームより下に
			SSSflag[i] = ROT_DOWN;

			// フレームの初期化
			StageSelectLogo[i].Init(flamesize.x,										// フレームテクスチャの横幅
									flamesize.y,										// フレームテクスチャの縦幅
									RelativeSX((FLAME_POS_X + (FLAME_POS_X_PLUS * i))),	// 配置位置X軸 (FLAME_POS_X_PLUS*i)ずれる
									SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),				// 配置位置Y軸 (FLAME_POS_Y_PLUS*i)ずれる
									STAGESELECT_TEX_FLAME);								// 読み込むテクスチャ

			// 未選択色
			StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.ReleaseBuffer();

	// ステージセレクト最大数メモリ解放
	for (int i = 0;i < SSS_MAX;i++)
	{
		StageSelectLogo[i].ReleaseBuffer();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStageSelect(void)
{

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
			// 上移動可能ならば
			if (UPflag == true)
			{
				// 選択フレームより上の場合
				if (SSSflag[i] == ROT_UP)
				{
					// 移動量を更新
					StageSelectLogo[i].Position.x -= speed.x;
					StageSelectLogo[i].Position.y += speed.y;

					// セレクトフラグ、または一つ後ろのフラグが選択中だったら
					if ((SELECTflag == ROT_SELECT) || (SSSflag[i + 1] == ROT_SELECT))
					{
						// テクスチャサイズ拡大
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);

						// カラー変更
						StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						// フラグを選択フレームへ
						SSSflag[i] = ROT_SELECT;

					}

					else
					{
						// テクスチャ更新
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					}

					// セレクトフラグをフレーム上へ
					SELECTflag = ROT_UP;
				}

				// 選択フレームより下の場合
				else if (SSSflag[i] == ROT_DOWN)
				{
					// 移動量を更新
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y += speed.y;


					// テクスチャ更新
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);


					// セレクトフラグをフレーム下へ
					SELECTflag = ROT_DOWN;
				}

				// 選択されているフレームなら
				else if (SSSflag[i] == ROT_SELECT)
				{

					// 移動量を更新
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y += speed.y;

					// テクスチャサイズ縮小
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);

					// カラー変更
					StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

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
			// 下移動可能ならば
			if (DOWNflag == true)
			{

				// 選択フレームより上の場合
				if (SSSflag[i] == ROT_UP)
				{
					// 移動量を更新
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y -= speed.y;


					// テクスチャ更新
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);


					// セレクトフラグをフレーム上へ
					SELECTflag = ROT_UP;
				}

				// 選択フレームより下の場合
				else if (SSSflag[i] == ROT_DOWN)
				{
					// 移動量を更新
					StageSelectLogo[i].Position.x -= speed.x;
					StageSelectLogo[i].Position.y -= speed.y;


					// セレクトフラグを選択中だったら
					if (SELECTflag == ROT_SELECT)
					{
						// テクスチャサイズ拡大
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);

						// カラー変更
						StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						// フラグを選択フレームへ
						SSSflag[i] = ROT_SELECT;

					}

					else
					{
						// テクスチャ更新
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					}


					// セレクトフラグをフレーム下へ
					SELECTflag = ROT_DOWN;

				}

				// 選択されているフレームなら
				else if (SSSflag[i] == ROT_SELECT)
				{
					// 移動量を更新
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y -= speed.y;

					// テクスチャサイズ縮小
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);

					// カラー変更
					StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					// セレクトフラグを選択中に
					SELECTflag = ROT_SELECT;

					// フラグを選択フレーム上へ
					SSSflag[i] = ROT_UP;

				}
			}

		}


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
	else if if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
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
		StageSelectLogo[i].Draw();
	}

	// 文字描画
	StageSelectText.Draw();

}

