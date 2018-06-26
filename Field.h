//=============================================================================
//
// 地面クラス <Field.h>
// Author : 初 景新
//
//=============================================================================
#ifndef _FIELD_CLASS_INCLUDE_H_
#define _FIELD_CLASS_INCLUDE_H_

#include "source/class/Aclass_object.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************
class FieldA : public class_ObjectA
{
	LPDIRECT3DTEXTURE9 *FieldTexture[2];
	int MapMax;

public:
	FieldA() {};
	~FieldA() {};

	void LoadTexture(void);
	void LoadStatus(float x, float y);

	void Init(float x, float y, int posX);
	void Update(void);
	void Draw(int sides, int map);
	void Uninit(void);

	void ReleaseBuffer(void);

private:

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************



#endif
