//=============================================================================
//
// HPUI�N���X <HPUI.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _UI_HP_CLASS_INCLUDE_H_
#define _UI_HP_CLASS_INCLUDE_H_

#include "main.h"
#include "source/class/ObjectBase.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_TEX_HP01 "data/TEXTURE/UI/HP01.png"
#define UI_TEX_HP02 "data/TEXTURE/UI/HP02.png"

#define HPUI_SIZE_X (25)
#define HPUI_SIZE_Y (25)

#define HPUI_POS_X (HPUI_SIZE_X*2 + 5)
#define HPUI_POS_Y (HPUI_SIZE_Y*2 + 10)

#define HPUI_MAX_HP (5)

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class UICHitPoint
{
	C2DUIPolygon *HP_UI;
	LPDIRECT3DTEXTURE9 Texture[2];
	int HP_MAX;

public:
	UICHitPoint() {};
	~UICHitPoint() {};

	void Init(int num, float sizeX, float sizeY, float posX, float posY);
	void Init(int num);
	void Update(void);
	void Draw(int hp);
	void Uninit(void);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



#endif
