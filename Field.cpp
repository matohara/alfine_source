//=============================================================================
//
// 地面クラス <Field.cpp>
// Author : 初 景新
//
//=============================================================================
#include "Field.h"


#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"


//----初期化処理--------
void FieldA::Init(float posX, float sizeX, float sizeY, LPDIRECT3DTEXTURE9 texture)
{
	// データの初期化
	this->Texture = NULL;
	this->Position = D3DXVECTOR3(posX, 0.0f, 0.0f);
	this->Rotation = D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f);

	this->LoadTexture(texture);						// テクスチャ読み込み
	this->LoadTextureStatus(sizeX, sizeY, 1.0f);	// 情報をセット
	this->MakeVertex();								// 頂点作成
}


//----初期化処理--------
void GameField::Init(float sizeX, float sizeY, const char *texture)
{
	this->LoadTexture(texture);
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Init(sizeX * 2.0f * iCnt, sizeX, sizeY, Texture);
	}
}

//----描画処理--------
void GameField::Draw()
{
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Draw();
	}
}

//----終了処理--------
void GameField::Uninit()
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Release();
	}
}

//----テクスチャを与える--------
void GameField::LoadTexture(const char *texture)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}

