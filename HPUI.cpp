//=============================================================================
//
// HPUIクラス <HPUI.cpp>
// Author : 初 景新
//
//=============================================================================
#include "HPUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----初期化処理--------
void UICHitPoint::Init(int num, float sizeX, float sizeY, float posX, float posY)
{
	// テクスチャ
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP01, &Texture[0]);
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP02, &Texture[1]);

	HP_MAX = num;
	HP_UI = new C2DUIPolygon[HP_MAX];

	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		HP_UI[iCnt].Init(sizeX, sizeY, posX + sizeX * 2 * (iCnt - (HP_MAX / 2)), posY);
	}
}
void UICHitPoint::Init(int num)
{
	// テクスチャ
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP01, &Texture[0]);
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP02, &Texture[1]);

	HP_MAX = num;
	HP_UI = new C2DUIPolygon[HP_MAX];

	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		HP_UI[iCnt].Init(HPUI_SIZE_X, HPUI_SIZE_Y, HPUI_POS_X * (float)(iCnt+1), HPUI_POS_Y);
	}
}

//----更新--------
void UICHitPoint::Update(void)
{

}

//----描画処理--------
void UICHitPoint::Draw(int hp)
{
	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		if (hp > 0)
		{
			HP_UI[iCnt].Draw(Texture[0]);
		}
		else
		{
			HP_UI[iCnt].Draw(Texture[1]);
		}
		hp--;
	}
}

//----終了処理--------
void UICHitPoint::Uninit(void)
{
	delete[] HP_UI;

	if (Texture[0] != NULL)
	{
		Texture[0]->Release();
		Texture[0] = NULL;
	}
	if (Texture[1] != NULL)
	{
		Texture[1]->Release();
		Texture[1] = NULL;
	}
}


