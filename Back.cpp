//=============================================================================
//
// 後壁 <Back.cpp>
// Author : 初 景新
//
//=============================================================================
#include "main.h"
#include "Back.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----初期化処理--------
void BGCBackFrontA::Init(float posZ, float posX, float fX, float fY, LPDIRECT3DTEXTURE9 texture)
{
	// 情報をリセット
	{
		this->Texture = NULL;		// テクスチャへのポインタ
		this->VtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
		this->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置座標
		this->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転角度
		this->Size = D3DXVECTOR2(0.0f, 0.0f);			// ポリゴンサイズ
		this->Scale = 1.0f;								// サイズ倍率
		this->TexPattern_X = 1;		// テクスチャパターン（横）
		this->TexPattern_Y = 1;		// テクスチャパターン（縦）
		this->AnimeCount = 0;		// アニメーションカウント
		this->AnimePattern = 0;		// 現在のアニメーションパターン番号
		this->ChangeAnimeTime = 0;	// アニメーション切り替え待時間
	}

	// 基本情報セット
	this->Size = { fX, fY };
	this->Position.z = posZ;
	this->Position.x = posX;

	// テクスチャ読み込み
	this->LoadTexture(texture);

	// 頂点設定
	this->MakeVertex();
	this->SetVertex();
}

//----終了処理--------
void BGCBackFrontA::Uninit(void)
{

}

//----頂点設定--------
void BGCBackFrontA::SetVertex(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-Size.x, Size.y * 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x, Size.y * 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x,          0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x,          0.0f, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

//----開放--------
void BGCBackFrontA::ReleaseBuffer(void)
{
	if (this->VtxBuff != NULL)
	{
		this->VtxBuff->Release();
		this->VtxBuff = NULL;
	}
}


//----初期化処理--------
void GameBackGround::Init(float posZ, float fX, float fY, const char *texture)
{
	this->LoadTexture(texture);
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		Parts[iCnt].Init(posZ, fX * 2.0f * iCnt, fX, fY, this->Texture);
	}
}

//----終了処理--------
void GameBackGround::Uninit(void)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		Parts[iCnt].ReleaseBuffer();
	}
}

//----描画処理--------
void GameBackGround::Draw(void)
{
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		this->Parts[iCnt].Draw();
	}
}

//----テクスチャ読み込み--------
void GameBackGround::LoadTexture(const char *texture)
{
	if (Texture != NULL)
	{	// テクスチャの開放
		Texture->Release();
		Texture = NULL;
	}
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}

