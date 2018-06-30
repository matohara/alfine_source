//=============================================================================
//
// Object-AClass <object.cpp>
// Author : 初 景新
//
//=============================================================================
#include "Aclass_object.h"


//=============================================================================
// < 3D基本オブジェクト >
// ・板ポリ
// ・MakeVertex()
// ・LoadTexture()
//=============================================================================

//----コンストラクタ--------
c3DBasicObjectClass::c3DBasicObjectClass()
{
	Texture = NULL;
	VtxBuff = NULL;
}

//----デストラクタ--------
c3DBasicObjectClass::~c3DBasicObjectClass()
{

}

//----テクスチャを与える--------
void c3DBasicObjectClass::LoadTexture(const char *texture)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}
void c3DBasicObjectClass::LoadTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->Texture = texture;
}


//=============================================================================
// < A型オブジェクト >
// ・板ポリ
// ・SetVertex()
//=============================================================================

//----コンストラクタ--------
class_ObjectA::class_ObjectA()
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

//----デストラクタ--------
class_ObjectA::~class_ObjectA()
{

}

//----描画処理--------
void class_ObjectA::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// αテスト設定
	//if (AlphaTestSwitch(0))
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件 (D3DCMP_GREATER)
	}

	// ラインティングを無効にする (ライトを当てると変になる場合がある)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを無効にする (ライトを当てると変になる場合がある)
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
void class_ObjectA::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// αテスト設定
	//if (AlphaTestSwitch(0))
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件 (D3DCMP_GREATER)
	}

	// ラインティングを無効にする (ライトを当てると変になる場合がある)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを無効にする (ライトを当てると変になる場合がある)
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//----描画処理(ビルボード)--------
void class_ObjectA::DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld;

	// αテスト設定
	//if (AlphaTestSwitch(0))
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件 (D3DCMP_GREATER)
	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ポリゴンを正面に向ける
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	//D3DXMatrixInverse(&WorldMatrix, NULL, &mtxView);
	//WorldMatrix._41 = 0.0f;
	//WorldMatrix._42 = 0.0f;
	//WorldMatrix._43 = 0.0f;

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, Scale, Scale, Scale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
void class_ObjectA::DrawBillboard(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld;

	// αテスト設定
	//if (AlphaTestSwitch(0))
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件 (D3DCMP_GREATER)
	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ポリゴンを正面に向ける
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	//D3DXMatrixInverse(&WorldMatrix, NULL, &mtxView);
	//WorldMatrix._41 = 0.0f;
	//WorldMatrix._42 = 0.0f;
	//WorldMatrix._43 = 0.0f;

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, Scale, Scale, Scale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//----描画処理(Y軸ビルボード)--------


//----頂点作成--------
int class_ObjectA::MakeVertex(void)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使用法　
		FVF_VERTEX_3D,			// 使用する頂点フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&VtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))					// NULLに設定
	{
		return 1;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// 法線の設定
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}

	return 0;
}

//----頂点座標設定--------
void class_ObjectA::SetVertex(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}
void class_ObjectA::SetVertex(D3DXCOLOR color)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

//----バッファ系開放--------
void class_ObjectA::ReleaseBuffer(void)
{
	if (Texture != NULL)
	{	// テクスチャの開放
		Texture->Release();
		Texture = NULL;
	}

	if (VtxBuff != NULL)
	{	// 頂点の開放
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}

//----テクスチャ情報書き込み--------
void class_ObjectA::LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = ptnX;
	TexPattern_Y = ptnY;
	ChangeAnimeTime = time;
}
void class_ObjectA::LoadTextureStatus(float sizX, float sizY, float scale)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = 1;
	TexPattern_Y = 1;
	ChangeAnimeTime = 1;
}

//----左右反転--------
void class_ObjectA::FlipX(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}


//=============================================================================
// < P型オブジェクト >
// ・板ポリ
//=============================================================================

//----コンストラクタ--------
class_ObjectP::class_ObjectP()
{

}

//----デストラクタ--------
class_ObjectP::~class_ObjectP()
{

}

//----描画処理--------

//----頂点作成--------


//----頂点座標設定--------
void class_ObjectP::SetVertex(float sizeX, float sizeY)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);

	// 頂点データをアンロックする
	VtxBuff->Unlock();
}


//----バッファ系開放--------



//=============================================================================
// < U型オブジェクト >
// ・2DUI
// ・LoadTexture()あり
//=============================================================================

//----コンストラクタ--------
class_ObjectU::class_ObjectU()
{
	// テクスチャへのポインタ
	Texture = NULL;
	// 頂点情報
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		Vertex[i].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Vertex[i].rhw = 0.0f;
		Vertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Vertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//----デストラクタ--------
class_ObjectU::~class_ObjectU()
{

}

//----描画処理--------
void class_ObjectU::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}
void class_ObjectU::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//----頂点作成--------
void class_ObjectU::MakeVertex(float sizeX, float sizeY, float posX, float posY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// 反射光の設定
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
void class_ObjectU::MakeVertex(float sizeX, float sizeY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// 反射光の設定
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//----頂点設定--------
void class_ObjectU::SetVertex(float sizeX, float sizeY, float posX, float posY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);
}
void class_ObjectU::SetVertex(float sizeX, float sizeY)
{
	// 頂点座標の設定
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);
}
void class_ObjectU::SetVertex(D3DXCOLOR color)
{
	// 反射光の設定
	Vertex[0].diffuse = color;
	Vertex[1].diffuse = color;
	Vertex[2].diffuse = color;
	Vertex[3].diffuse = color;
}

//----位置設定(現在値加算)--------
void class_ObjectU::SetPosition(float posX, float posY)
{
	// 頂点座標の設定
	Vertex[0].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[1].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[2].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[3].vtx += D3DXVECTOR3(posX, posY, 0.0f);
}

//----テクスチャ座標設定--------
void class_ObjectU::SetTexture(int num, int ix, int iy)
{
	int x = num % ix;
	int y = num / ix;
	float sizeX = 1.0f / ix;
	float sizeY = 1.0f / iy;
	Vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX,         (float)(y)* sizeY);
	Vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	Vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX,         (float)(y)* sizeY + sizeY);
	Vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//----テクスチャリンク--------
LPDIRECT3DTEXTURE9 class_ObjectU::GetTextureAddress(LPDIRECT3DTEXTURE9 *texture)
{
	*texture = Texture;
	return Texture;
}

//----バッファ系開放--------
void class_ObjectU::ReleaseBuffer(void)
{
	if (Texture != NULL)
	{// テクスチャの開放
		Texture->Release();
		Texture = NULL;
	}
}

//----テクスチャを与える--------
void class_ObjectU::LoadTexture(const char *texture)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}
void class_ObjectU::LoadTexture(LPDIRECT3DTEXTURE9 texture)
{
	// テクスチャの読み込み
	Texture = texture;
}

