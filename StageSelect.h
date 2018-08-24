//=============================================================================
//
// ステージセレクト処理 [StageSelect.h]
// Author : 眞戸原史也
//
//=============================================================================
#ifndef _STAGESELECT_INCLUDE_H_
#define _STAGESELECT_INCLUDE_H_

#include "Library\ObjectBase2D.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/メニュー画面背景.png"
#define STAGESELECT_TEX_UI		     "data/TEXTURE/UI/OptionBar.png"

#define BG_STAGE_ONE				"data/TEXTURE/STAGEVIEW/イメージ１.png"		// テクスチャ：ステージ１
#define BG_STAGE_TWO				"data/TEXTURE/STAGEVIEW/イメージ２.png"		// テクスチャ：ステージ２
#define BG_STAGE_THREE				"data/TEXTURE/STAGEVIEW/イメージ３.png"		// テクスチャ：ステージ３
#define BG_STAGE_FOUR				"data/TEXTURE/STAGEVIEW/イメージ４.png"		// テクスチャ：ステージ４
#define BG_STAGE_POS_X				(300)										// BG配置x軸(y軸はセンタースクリーン)
#define BG_STAGE_WIDTH				(300)										// BGテクスチャ横幅
#define BG_STAGE_HEIGHT				(250)										// BGテクスチャ高さ
#define BG_FADE_SPEED				(2)											// 背景のフェード速度
#define BG_BASE_ALPHA				(1)											// α初期値

#define STAGESELECT_TEXT_ONE		"data/TEXTURE/STAGEVIEW/StageLogo000.png"	// ステージセレクトテクスチャ：ステージ１
#define STAGESELECT_TEXT_TWO		"data/TEXTURE/STAGEVIEW/StageLogo01.png"	// ステージセレクトテクスチャ：ステージ１
#define STAGESELECT_TEXT_THREE		"data/TEXTURE/STAGEVIEW/StageLogo02.png"	// ステージセレクトテクスチャ：ステージ１
#define STAGESELECT_TEXT_FOUR		"data/TEXTURE/STAGEVIEW/StageLogo03.png"	// ステージセレクトテクスチャ：ステージ１
#define STAGESELECT_TEX_SELECT_SIZE	D3DXVECTOR2(280.0f, 90.0f)				// 選択した時のテクスチャの大きさ
#define STAGESELECT_TEX_SIZE		D3DXVECTOR2(24
0.0f, 40.0f)					// 文字テクスチャの大きさ
#define FLAME_TEX_X					(0.69f)										// 文字のx軸配置倍率

#define STAGESELECT_TEX_FLAME      "data/TEXTURE/UI/Frame00.png"		// ステージセレクトのフレームテクスチャ
#define STAGESELECT_SELECT_SIZE		D3DXVECTOR2(280.0f, 100.0f)			// 選択した時のテクスチャの大きさ
#define STAGESELECT_FLAME_SIZE		D3DXVECTOR2(240.0f, 60.0f)			// フレームテクスチャの大きさ
#define FLAME_POS_X					(0.7f)								// フレームのx軸配置倍率
#define FLAME_POS_X_PLUS			(0.05f)								// フレームのx軸配置倍率増加値
#define FLAME_POS_Y_PLUS			(120.0f)							// フレームのy軸配置倍率増加値

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
	ROT_DOWN = -1,	// ダウン
	ROT_SELECT,		// セレクト
	ROT_UP,			// アップ
	ROT_MAX			// バレルセレクト最大数
};


//*****************************************************************************
// クラス設計
//*****************************************************************************

/*バレルクラス */
class Barrel : public C2DObject
{
public:
	Barrel() {};			// コンストラクタ
	~Barrel() {};			// デストラクタ

	// ポジション移動関数
	void LogoMove(float posX, float posY)
	{
		Position.x += posX;		// x軸
		Position.y += posY;		// y軸
	}

	// ロゴサイズ更新関数
	void LogoSize(float sizeX, float sizeY)
	{

		float risc = 1.41421356f;
		Vertex[0].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) + Angle) * risc * sizeX * Scale;
		Vertex[0].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) + Angle) * risc * sizeY * Scale;
		Vertex[0].vtx.z = 0.0f;
		Vertex[1].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) - Angle) * risc * sizeX * Scale;
		Vertex[1].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) - Angle) * risc * sizeY * Scale;
		Vertex[1].vtx.z = 0.0f;
		Vertex[2].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) - Angle) * risc * sizeX * Scale;
		Vertex[2].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) - Angle) * risc * sizeY * Scale;
		Vertex[2].vtx.z = 0.0f;
		Vertex[3].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) + Angle) * risc * sizeX * Scale;
		Vertex[3].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) + Angle) * risc * sizeY * Scale;
		Vertex[3].vtx.z = 0.0f;

	}

};

/*セレクト背景クラス */
class StageSelectBg : public C2DObject
{
public:
	StageSelectBg() {};			// コンストラクタ
	~StageSelectBg() {};		// デストラクタ

	// 背景フェードイン関数
	void BgSetAlpha(int alpha)
	{

		// α値を反映
		Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);

	}


};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

#endif
