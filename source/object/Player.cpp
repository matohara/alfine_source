//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 初 景新
//
//=============================================================================
#include "../../main.h"
#include "../../input.h"

#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----プレイヤー情報セット--------
void PlayerA::LoadPlayerStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, 7, 1, 10);

	Position = D3DXVECTOR3(0.0f, y, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----ルート読み込み--------
void PlayerA::LoadRoute(void)
{
	// Output 受け取る
	FILE *fp = fopen(DATAFILE_PLAYER_ROUTE, "r");	// ファイルを開く

	// ファイルが開けたかチェック
	if (fp == NULL)
	{
		MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Open\"", MB_YESNO);
	}

	// マップデータを取る
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#MAP_NUMBER"))
		{
			MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Read\"", MB_YESNO);
		}
	}

	fscanf(fp, "%d", &MapMax);
	PointMax = new int[MapMax];

	// ファイルから読み込む
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		fscanf(fp, "%d", &PointMax[iCnt]);
	}

	// ルートデータを取る
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#ROUTE_DATA"))
		{
			MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// メモリ確保
	Route = new PlayerRoute*[MapMax];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		Route[iCnt] = new PlayerRoute[PointMax[iCnt]];
	}

	char skep;
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		for (int iCnt2 = 0; iCnt2 < PointMax[iCnt]; iCnt2++)
		{
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.x);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.y);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.z);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%d", &Route[iCnt][iCnt2].Time);
			fscanf(fp, "%c", &skep);
		}
	}

	fclose(fp);	// ファイル操作終了

}


//----初期化処理--------
void PlayerA::Init(void)
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

		Route = NULL;		// 移動ルート保存用ポインター
		MapNumber = 0;		// 次のマップ番号
		NextPoint = 0;		// 次の移動先番号
		RouteCounter = 0;	// 移動進行度
		PointMax = NULL;	// 移動ポイント数
		MapMax = 0;			// マップ最大数
	}

	// テクスチャ読み込み
	LoadTexture(TEXTURE_PLAYER2);

	// プレイヤー情報をセット
	LoadPlayerStatus(21.4f, 32.4f);

	// 初期テクスチャに設定
	SetTexture();

	// 移動ルートを設定
	LoadRoute();
}

//----更新処理--------
int PlayerA::Update(void)
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

	if (NextPoint == 0)
	{// 原点は瞬時移動
		Position = Route[MapNumber][NextPoint].Point;
		NextPoint++;
	}
	else
	{// 指定ポイントまで移動
		// 移動ベクトルを求める
		Position += (Route[MapNumber][NextPoint].Point - Route[MapNumber][NextPoint - 1].Point) / (float)Route[MapNumber][NextPoint].Time;
		RouteCounter++;
		if (RouteCounter == Route[MapNumber][NextPoint].Time)
		{// 指定フレーム数移動終了
			RouteCounter = 0;
			NextPoint++;
		}

		// 全ポイントを移動後次のマップへ
		if (NextPoint >= PointMax[MapNumber])
		{
			MapNumber++;
			NextPoint = 0;
		}

		// *全マップ終了後終了
		if (MapNumber >= MapMax)
		{
			MapNumber = MapMax - 1;
			return 1;
		}
	}

	return 0;
}

//----描画処理--------
void PlayerA::Draw(void)
{
	// 描画
	this->class_ObjectA::DrawBillboard();
}

//----終了処理--------
void PlayerA::Uninit(void)
{
	// テクスチャバッファ開放
	ReleaseBuffer();

	// ルートデータメモリ開放
	ReleaseRouteData();
}

//----メモリ開放--------
void PlayerA::ReleaseRouteData(void)
{
	for (int i = 0; i < MapMax; i++)
	{
		delete[] Route[i];
	}
	delete[] Route;
	Route = NULL;

	delete[] PointMax;
	PointMax = NULL;
}

//--テクスチャ座標の設定--//
void PlayerA::SetTexture(void)
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
void PlayerB::LoadPlayerStatus(int bx, int by, float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, bx, by, 10);

	Position = D3DXVECTOR3(-1200.0f, y, GAME_PLAYER_ZPOS);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Speed = 2;

	MakeVertex();
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
void PlayerB::GoPoint(D3DXVECTOR3 vec)
{
	Position += vec;
}

//----0テクスチャ--------
void PlayerB::ReSetTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----初期化処理--------
void PlayerB::Init(const char *texture)
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

		Speed = 0.0f;		// 移動速度(総合時間)
		MapNumber = 0;		// 次のマップ番号
		RouteCounter = 0;	// 移動進行度
		MapMax = 4;			// マップ最大数
	}

	// テクスチャ読み込み
	LoadTexture(texture);

	// プレイヤー情報をセット
	LoadPlayerStatus(1, 1, 19.0f, 30.5f);

	// 初期テクスチャに設定
	SetTexture();
}
void PlayerB::Init(const char *texture, int x, int y)
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

		Speed = 0.0f;		// 移動速度(総合時間)
		MapNumber = 0;		// 次のマップ番号
		RouteCounter = 0;	// 移動進行度
		MapMax = 4;			// マップ最大数
	}

	// テクスチャ読み込み
	LoadTexture(texture);

	// プレイヤー情報をセット
	LoadPlayerStatus(x, y, 21.4f, 32.4f);

	// 初期テクスチャに設定
	SetTexture();
}

//----更新処理--------
int PlayerB::Update(void)
{
	Animation();

	Position.x += Speed;

	if (Position.x > 1100.0f)
	{
		MapNumber++;
		Position.x = -1100.0f;
	}

	// *全マップ終了後終了
	if (MapNumber >= MapMax)
	{
		MapNumber = MapMax - 1;
		return 1;
	}

	PrintDebugProcess("プレイヤー位置 : （%f, %f, %f）\n", Position.x, Position.y, Position.z);
	return 0;
}

//----描画処理--------
void PlayerB::Draw(void)
{
	// 描画
	this->class_ObjectA::DrawBillboard();
}

//----終了処理--------
void PlayerB::Uninit(void)
{
	// テクスチャバッファ開放
	ReleaseBuffer();
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

//----描画処理--------
void PlayerC::Draw(void)
{
	// 描画
	this->class_ObjectA::DrawBillboard();
}

//----終了処理--------
void PlayerC::Uninit(void)
{
	// テクスチャバッファ開放
	ReleaseBuffer();
}

//----テクスチャ反転--------
void PlayerC::FlipX(void)
{
	D3DXVECTOR2 tex;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		tex = pVtx[0].tex;
		pVtx[0].tex = pVtx[1].tex;
		pVtx[1].tex = tex;
		tex = pVtx[2].tex;
		pVtx[2].tex = pVtx[3].tex;
		pVtx[3].tex = tex;

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
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


