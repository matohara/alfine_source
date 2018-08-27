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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

#endif
