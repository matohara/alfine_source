//=============================================================================
//
// �X�e�[�^�X�o�[UI�N���X <StatusBarUI.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _UI_STATUSBAR_CLASS_INCLUDE_H_
#define _UI_STATUSBAR_CLASS_INCLUDE_H_

#include "main.h"
#include "Library\ObjectBase2D.h"


/* BackPolygon */
#define UI_TEX_BACKPOLY "data/TEXTURE/UI/FrontUI.png"

#define BACKPOLY_SIZE_X (SCREEN_CENTER_X)
#define BACKPOLY_SIZE_Y (67.6f)

#define BACKPOLY_POS_X (SCREEN_CENTER_X)
#define BACKPOLY_POS_Y (SCREEN_HEIGHT - BACKPOLY_SIZE_Y)

/* Logo Option */
#define LOGOUI_TEX_BACKPOLY "data/TEXTURE/LOGO/Option.png"

#define LOGO_OPTION_SIZE_Y (BACKPOLY_SIZE_Y / 2)
#define LOGO_OPTION_SIZE_X (LOGO_OPTION_SIZE_Y * 2.68f)

#define LOGO_OPTION_POS_X (LOGO_OPTION_SIZE_X + 40)
#define LOGO_OPTION_POS_Y (BACKPOLY_POS_Y + 30)

/* N / X */
#define UI_TEX_NUMBER "data/TEXTURE/UI/Number.png"
#define UI_TEX_SLASH  "data/TEXTURE/UI/Slash.png"

#define UI_NvX_N_SIZE_Y (BACKPOLY_SIZE_Y / 2)
#define UI_NvX_N_SIZE_X (UI_NvX_N_SIZE_Y / 2)
#define UI_NvX_X_SIZE_X (UI_NvX_N_SIZE_X * 0.8f)
#define UI_NvX_X_SIZE_Y (UI_NvX_N_SIZE_Y * 0.8f)
#define UI_NvX_SLASH_SIZE_X (UI_NvX_N_SIZE_X)
#define UI_NvX_SLASH_SIZE_Y (UI_NvX_N_SIZE_Y)

#define UI_NvX_N_POS_X (SCREEN_WIDTH - (UI_NvX_N_SIZE_X * 2 + 12 + UI_NvX_SLASH_SIZE_X * 2 + UI_NvX_X_SIZE_X * 2) + 10)
#define UI_NvX_N_POS_Y (BACKPOLY_POS_Y + 15)
#define UI_NvX_SLASH_POS_X (UI_NvX_N_POS_X + UI_NvX_N_SIZE_X + 12)
#define UI_NvX_SLASH_POS_Y (UI_NvX_N_POS_Y)
#define UI_NvX_X_POS_X (UI_NvX_SLASH_POS_X + UI_NvX_SLASH_SIZE_X)
#define UI_NvX_X_POS_Y (UI_NvX_N_POS_Y + 5)


class UICNvX
{
	UI2DNumber N;
	UI2DNumber X;
	UI2DNumber Slash;

public:
	void Init(float size, float posX, float posY);
	void Update(int num);
	void Draw(void);
	void Uninit(void);

private:

};




#endif
