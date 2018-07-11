//=============================================================================
//
// 後壁 <Back.h>
// Author : 初 景新
//
//=============================================================================
#ifndef _BACK_INCLUDE_H_
#define _BACK_INCLUDE_H_

#include "Library\ObjectBase3D.h"

// マクロ定義
#define BACK_NUM (14)

#define TEXTURE_FILE_BACK_B  "data/STAGE/BackTextureB.txt"
#define TEXTURE_FILE_BACK_F  "data/STAGE/BackTextureF.txt"

#define BACK_TEX_ONSIDE_FRONT  "data/チュートリアル/OnSideFront.png"
#define BACK_TEX_ONSIDE_BACK   "data/チュートリアル/OnSideBack.jpg"
#define BACK_TEX_OFFSIDE_FRONT "data/チュートリアル/OffSideFront.png"
#define BACK_TEX_OFFSIDE_BACK  "data/チュートリアル/OffSideBack.png"


//*****************************************************************************
// クラス設計
//*****************************************************************************
class BGCBackFrontA : public C3DPolygonObject
{
public:
	BGCBackFrontA() {};
	~BGCBackFrontA() {};

	void Init(float posZ, float posX, float fX, float fY, LPDIRECT3DTEXTURE9 texture);
	void Uninit(void);

	void SetVertex(void);
	void ReleaseBuffer(void);

private:

};


class GameBackGround
{
	LPDIRECT3DTEXTURE9 Texture;
	BGCBackFrontA Parts[BACK_NUM];

public:

	void Init(float posZ, float fX, float fY, const char *texture);
	void Draw(void);
	void Uninit(void);

	void LoadTexture(const char *texture);

private:

};



#endif
