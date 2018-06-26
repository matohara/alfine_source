//============================================================================
//
// 後壁 <Back.cpp>
// Author : 初 景新
//
//=============================================================================
#include "main.h"
#include "Back.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----テクスチャをロード--------
void BGCBackFront::LoadTexture(const char *file)
{
	// Output 受け取る
	FILE *fp = fopen(file, "r");	// ファイルを開く

	if (fp == NULL)
	{// ファイルが開けたかチェック
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

	// メモリ確保
	fscanf(fp, "%d", &MapMax);
	BackTexture[0] = new LPDIRECT3DTEXTURE9[MapMax];
	BackTexture[1] = new LPDIRECT3DTEXTURE9[MapMax];

	// ファイルパスを読み込む
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#BACK_TEXTURE"))
		{
			MessageBox(GethWnd(), "ファイルの読み込みに失敗しました", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// テクスチャ読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char pass[256];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		// 表テクスチャ読み込み
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &BackTexture[0][iCnt]);
		// 裏テクスチャ読み込み
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &BackTexture[1][iCnt]);
	}

	fclose(fp);	// ファイル操作終了

}

//----初期化処理--------
void BGCBackFront::Init(float posZ, float fX, float fY, const char *file, int posX)
{
	// 情報をリセット
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

	// 基本情報セット
	Size = { fX, fY };
	Position.x = fX * 2 * posX;
	Position.z = posZ;

	// テクスチャ読み込み
	LoadTexture(file);

	// 頂点設定
	MakeVertex();
	SetVertex();
}

//----終了処理--------
void BGCBackFront::Uninit(void)
{
	this->class_ObjectA::ReleaseBuffer();

	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		if (BackTexture[0][iCnt] != NULL)
		{
			BackTexture[0][iCnt]->Release();
			BackTexture[0][iCnt] = NULL;
		}
		if (BackTexture[1][iCnt] != NULL)
		{
			BackTexture[1][iCnt]->Release();
			BackTexture[1][iCnt] = NULL;
		}
	}
	delete[] BackTexture[0];
	delete[] BackTexture[1];
	BackTexture[0] = NULL;
	BackTexture[1] = NULL;

}

//----更新処理--------
void BGCBackFront::Update(void)
{

}

//----描画処理--------
void BGCBackFront::Draw(int sides, int map)
{
	this->class_ObjectA::DrawBillboard(BackTexture[sides][map]);
}


//----頂点設定--------
void BGCBackFront::SetVertex(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x, Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, 0.0f, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

