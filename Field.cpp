//=============================================================================
//
// 地面クラス <Field.cpp>
// Author : 初 景新
//
//=============================================================================
#include "Field.h"


#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"


//----初期化処理--------
void FieldA::Init(float posX, float sizeX, float sizeY, LPDIRECT3DTEXTURE9 texture, int flip)
{
	// データの初期化
	this->Texture = NULL;
	this->Position = D3DXVECTOR3(posX, 0.0f, 0.0f);
	this->Rotation = D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f);

	this->LoadTexture(texture);						// テクスチャ読み込み
	this->LoadTextureStatus(sizeX, sizeY, 1.0f);	// 情報をセット
	this->MakeVertex();								// 頂点作成
	if (flip)
		this->FlipTexture();						// テクスチャ反転
}

//----テクスチャー反転--------
void FieldA::FlipTexture()
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//----テクスチャ反転--------
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}


//----初期化処理--------
void GameField::Init(float sizeX, float sizeY, const char *texture)
{
	this->LoadTexture(texture);
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Init(sizeX * 2.0f * iCnt, sizeX, sizeY, Texture, iCnt%2);
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

