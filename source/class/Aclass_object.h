//=============================================================================
//
// Object-AClass <object.h>
// Author : 初 景新
//
//=============================================================================
#ifndef __CLASS_OBJECT_CLASS_INCLUDE_H__
#define __CLASS_OBJECT_CLASS_INCLUDE_H__


#include "../../main.h"
#include "../../Camera.h"

using namespace std;

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************
/* 基本クラス */
class c3DBasicObjectClass
{

protected:
	LPDIRECT3DTEXTURE9		Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	c3DBasicObjectClass();
	~c3DBasicObjectClass();

//	virtual void Draw(void);						// 描画処理
//	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理(テクスチャ指定)

	virtual void LoadTexture(const char *texture);
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);

private:

};


/* オブジェクトAクラス */
class class_ObjectA : public c3DBasicObjectClass
{

protected:
	D3DXVECTOR3 Position;	// 位置座標
	D3DXVECTOR3 Rotation;	// 回転角度
	D3DXVECTOR2 Size;		// ポリゴンサイズ
	float Scale;			// サイズ倍率

	int TexPattern_X;		// テクスチャパターン（横）
	int TexPattern_Y;		// テクスチャパターン（縦）
	int AnimeCount;			// アニメーションカウント
	int AnimePattern;		// 現在のアニメーションパターン番号
	int ChangeAnimeTime;	// アニメーション切り替え待時間

	virtual int MakeVertex(void);
	virtual void SetVertex(void);				// 頂点座標設定@頂点位置のみ
	virtual void SetVertex(D3DXCOLOR color);	// 頂点座標設定@頂点色込み

public:
	class_ObjectA();
	~class_ObjectA();

	virtual void Draw(void);						// 描画処理
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理(テクスチャ指定)
	virtual void DrawBillboard(void);						// 描画処理(ビルボード)
	virtual void DrawBillboard(LPDIRECT3DTEXTURE9 texture);	// 描画処理(ビルボード)(テクスチャ指定)

	virtual void ReleaseBuffer(void);	// バッファ系開放
	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);	//テクスチャ情報@アニメーションなし

	virtual void FlipX(void);	// 左右反転

private:

};


/* オブジェクトPクラス */
class class_ObjectP : public c3DBasicObjectClass
{
public:
	class_ObjectP();
	~class_ObjectP();

//	virtual int MakeVertex(D3DXVECTOR3 size, D3DXVECTOR3 nor);
	virtual void SetVertex(float sizeX, float sizeY);

private:

};


/* オブジェクトUクラス */
class class_ObjectU
{
	
protected:
	LPDIRECT3DTEXTURE9	Texture;	// テクスチャへのポインタ

	virtual void MakeVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点作成
	virtual void MakeVertex(float sizeX, float sizeY);

public:
	VERTEX_2D	Vertex[NUM_VERTEX];	// 頂点情報

	class_ObjectU();
	~class_ObjectU();

	virtual void Draw(void);						// 描画処理(通常)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// 描画処理(通常)(テクスチャ指定)

	virtual void ReleaseBuffer(void);	// バッファ系開放
	virtual void LoadTexture(const char *texture);
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);

	virtual void SetVertex(float sizeX, float sizeY, float posX, float posY);	// 頂点座標設定
	virtual void SetVertex(float sizeX, float sizeY);
	virtual void SetVertex(D3DXCOLOR color);

	virtual void SetPosition(float posX, float posY);	// 移動
	virtual void SetTexture(int num, int ix, int iy);	// テクスチャ座標設定

	virtual LPDIRECT3DTEXTURE9 GetTextureAddress(LPDIRECT3DTEXTURE9 *texture);

private:

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
