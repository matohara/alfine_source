//=============================================================================
//
// プレイヤー処理 <Player.cpp>
// Author : 初 景新
//
//=============================================================================
#include "Player.h"
#include "Library\Input.h"


//----プレイヤー情報セット--------
void PlayerB::LoadPlayerStatus(float posX, int bx, int by, float x, float y)
{
	this->LoadTextureStatus(x, y, 1.0f, bx, by, 10);
	this->Position = D3DXVECTOR3(posX, y, GAME_PLAYER_ZPOS);
	this->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Speed = PLAYER_MOVE_SPEED;
	this->MakeVertex();
}

//----アニメーション--------
void PlayerB::Animation(void)
{
	if ((TexPattern_X * TexPattern_Y) > 1)// テクスチャ種類が一種の場合はスキップ
	{
		/* アニメーション */
		AnimeCount++;
		if ((AnimeCount % ChangeAnimeTime) == 0)
		{
			// パターンの切り替え
			AnimePattern = (AnimePattern + 1) % (TexPattern_X * TexPattern_Y);
			// テクスチャ座標を設定
			SetTexture();
		}
	}
}

//----移動--------
void PlayerB::Move(D3DXVECTOR3 vec)
{
	Position += vec;
}

//----0テクスチャ--------
void PlayerB::SetZeroTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----初期化処理--------
void PlayerB::Init(const char *texture)
{
	// 情報リセット
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
		this->Speed = 0.0f;	// 移動速度
	}
	this->LoadTexture(texture);							// テクスチャ読み込み
	this->LoadPlayerStatus(-512, 1, 1, 19.0f, 30.5f);	// プレイヤー情報をセット
	this->SetTexture();									// 初期テクスチャに設定
}
void PlayerB::Init(const char *texture, int x, int y)
{
	// 情報リセット
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
		this->Speed = 0.0f;	// 移動速度(総合時間)
	}
	this->LoadTexture(texture);							// テクスチャ読み込み
	this->LoadPlayerStatus(-512, x, y, 21.4f, 32.4f);	// プレイヤー情報をセット
	this->SetTexture();									// 初期テクスチャに設定
}

//----更新処理--------
int PlayerB::Update(void)
{
	Animation();

	Position.x += Speed;

	if (Position.x > 16500)
	{
		return 1;
	}

	PrintDebugProcess("プレイヤー位置 : （%f, %f, %f）\n", Position.x, Position.y, Position.z);
	return 0;
}

//----終了処理--------
void PlayerB::Uninit(void)
{
	// テクスチャバッファ開放
	Release();
}

//--テクスチャ座標の設定--//
void PlayerB::SetTexture(void)
{
	// テクスチャ座標の設定
	int x = AnimePattern % TexPattern_X;
	int y = AnimePattern / TexPattern_X;
	float sizeX = 1.0f / TexPattern_X;
	float sizeY = 1.0f / TexPattern_Y;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}


//----プレイヤー情報セット--------
void PlayerC::LoadPlayerStatus(int bx, int by, float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, bx, by, 10);

	Position = D3DXVECTOR3(0.0f, y, GAME_PLAYER_ZPOS);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----アニメーション--------
void PlayerC::Animation(void)
{
	if ((TexPattern_X * TexPattern_Y) > 1)// テクスチャ種類が一種の場合はスキップ
	{
		/* アニメーション */
		AnimeCount++;
		if ((AnimeCount % ChangeAnimeTime) == 0)
		{
			// パターンの切り替え
			AnimePattern = (AnimePattern + 1) % (TexPattern_X * TexPattern_Y);
			// テクスチャ座標を設定
			SetTexture();
		}
	}
}

//----移動--------
void PlayerC::GoPoint(float x)
{
	Position.x += x;
}
void PlayerC::SetPosition(D3DXVECTOR3 pos)
{
	Position = pos;
}
void PlayerC::SetPosition(float x)
{
	Position.x = x;
}

//----0テクスチャ--------
void PlayerC::ReSetTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----初期化処理--------
void PlayerC::Init(const char *texture)
{
	// 情報リセット
	{
		Texture = NULL;		// テクスチャへのポインタ
		VtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置座標
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転角度
		Size = D3DXVECTOR2(0.0f, 0.0f);				// ポリゴンサイズ
		Scale = 1.0f;								// サイズ倍率
		TexPattern_X = 1;		// テクスチャパターン（横）
		TexPattern_Y = 1;		// テクスチャパターン（縦）
		AnimeCount = 0;			// アニメーションカウント
		AnimePattern = 0;		// 現在のアニメーションパターン番号
		ChangeAnimeTime = 0;	// アニメーション切り替え待時間
	}

	// テクスチャ読み込み
	LoadTexture(texture);

	// プレイヤー情報をセット
	LoadPlayerStatus(1, 1, 30.0f, 30.0f);

	// 初期テクスチャに設定
	SetTexture();
}
void PlayerC::Init(const char *texture, int x, int y)
{
	// 情報リセット
	{
		Texture = NULL;		// テクスチャへのポインタ
		VtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置座標
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転角度
		Size = D3DXVECTOR2(0.0f, 0.0f);				// ポリゴンサイズ
		Scale = 1.0f;								// サイズ倍率
		TexPattern_X = 1;		// テクスチャパターン（横）
		TexPattern_Y = 1;		// テクスチャパターン（縦）
		AnimeCount = 0;			// アニメーションカウント
		AnimePattern = 0;		// 現在のアニメーションパターン番号
		ChangeAnimeTime = 0;	// アニメーション切り替え待時間
	}

	// テクスチャ読み込み
	LoadTexture(texture);

	// プレイヤー情報をセット
	LoadPlayerStatus(x, y, 21.0f, 30.0f);

	// 初期テクスチャに設定
	SetTexture();
}

//----更新処理--------
void PlayerC::Update(float x)
{
	Animation();

	Position.x = x;
}

//----終了処理--------
void PlayerC::Uninit(void)
{
	// テクスチャバッファ開放
	Release();
}

//--テクスチャ座標の設定--//
void PlayerC::SetTexture(void)
{
	// テクスチャ座標の設定
	int x = AnimePattern % TexPattern_X;
	int y = AnimePattern / TexPattern_X;
	float sizeX = 1.0f / TexPattern_X;
	float sizeY = 1.0f / TexPattern_Y;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}


