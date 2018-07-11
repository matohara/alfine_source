//=============================================================================
//
// �K�C�hUI�N���X <Guide.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _UI_GUIDE_CLASS_INCLUDE_H_
#define _UI_GUIDE_CLASS_INCLUDE_H_


#include "Library\ObjectBase3D.h"
#include "main.h"


#define UI_TEX_GUIDE  "data/TEXTURE/UI/Guide.png"


class UICGuide : public C3DPolygonObject
{
	D3DXCOLOR TexColor;

public:
	bool Active;
	UICGuide() {};
	~UICGuide() {};

	int Init();
	int Update();
	void Uninit();

	void SetGuideUI(D3DXVECTOR3 pos);

private:

};





#endif
