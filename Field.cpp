//=============================================================================
//
// 地面クラス <Field.cpp>
// Author : 初 景新
//
//=============================================================================
#include "input.h"
#include "Field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************

//----テクスチャをロード--------
void FieldA::LoadTexture(void)
{
	// Output 受け取る
	FILE *fp = fopen(TEXTURE_FILE_FIELD, "r");	// ファイルを開く

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
	FieldTexture[0] = new LPDIRECT3DTEXTURE9[MapMax];
	FieldTexture[1] = new LPDIRECT3DTEXTURE9[MapMax];

	// ファイルパスを読み込む
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#FIELD_TEXTURE"))
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
		D3DXCreateTextureFromFile(pDevice, pass, &FieldTexture[0][iCnt]);
		// 裏テクスチャ読み込み
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &FieldTexture[1][iCnt]);
	}

	fclose(fp);	// ファイル操作終了

}

//----情報をセット--------
void FieldA::LoadStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f);

	MakeVertex();
}


//----初期化処理--------
void FieldA::Init(float x, float y, int posX)
{
	// データの初期化
	FieldTexture[0] = NULL;
	FieldTexture[1] = NULL;
	MapMax = 0;

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f);
	Position.x = x * 2 * posX;

	// テクスチャ読み込み
	//if (posX == 0)
	{
		LoadTexture();
	}

	// 情報をセット
	LoadStatus(x, y);
}

//----更新--------
void FieldA::Update(void)
{

}

//----描画処理--------
void FieldA::Draw(int sides, int map)
{
	this->class_ObjectA::Draw(FieldTexture[sides][map]);
}

//----終了処理--------
void FieldA::Uninit(void)
{
	// バッファ開放
	this->FieldA::ReleaseBuffer();
	this->class_ObjectA::ReleaseBuffer();
}


//----バッファ開放--------
void FieldA::ReleaseBuffer(void)
{
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		if (FieldTexture[0][iCnt] != NULL)
		{
			FieldTexture[0][iCnt]->Release();
			FieldTexture[0][iCnt] = NULL;
		}
		if (FieldTexture[1][iCnt] != NULL)
		{
			FieldTexture[1][iCnt]->Release();
			FieldTexture[1][iCnt] = NULL;
		}
	}
	delete[] FieldTexture[0];
	delete[] FieldTexture[1];

	FieldTexture[0] = NULL;
	FieldTexture[1] = NULL;
}

