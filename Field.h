//=============================================================================
//
// 地面クラス <Field.h>
// Author : 初 景新
//
//=============================================================================
#ifndef _FIELD_CLASS_INCLUDE_H_
#define _FIELD_CLASS_INCLUDE_H_

#include "Library\ObjectBase3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define FIELD_MUN (18)

//*****************************************************************************
// クラス設計
//*****************************************************************************
class FieldA : public C3DPolygonObject
{
public:
	FieldA() {};
	~FieldA() {};

	void Init(float posX, float sizeX, float sizeY, LPDIRECT3DTEXTURE9 texture, int flip);
	void FlipTexture();
};


class GameField
{
	LPDIRECT3DTEXTURE9 Texture;
	FieldA Parts[FIELD_MUN];

public:
	void Init(float sizeX, float sizeY, const char *texture);
	void Draw(void);
	void Uninit(void);

	void LoadTexture(const char *texture);

};





#endif
