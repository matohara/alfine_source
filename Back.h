//=============================================================================
//
// ��� <Back.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _BACK_INCLUDE_H_
#define _BACK_INCLUDE_H_

#include "Library\ObjectBase3D.h"

// �}�N����`
#define BACK_NUM (14)


/* �ǖ{�� */
class BGCBackFrontA : public C3DPolygonObject
{
public:
	BGCBackFrontA() {};
	~BGCBackFrontA() {};

	void Init(float posZ, float posX, float fX, float fY, LPDIRECT3DTEXTURE9 texture, int flip);
	void Uninit(void);

	void SetVertex(int flip);
	void ReleaseBuffer(void);

private:

};

/* �ǃN���X */
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
