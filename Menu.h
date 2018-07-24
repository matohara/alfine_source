//=============================================================================
//
// ÉÅÉjÉÖÅ[èàóù <Menu.h>
// Author : èâ åiêV
//
//=============================================================================
#ifndef _MENU_INCLUDE_H_
#define _MENU_INCLUDE_H_

#include "Library\ObjectBase2D.h"


enum MENUITEM
{
	RESTART = 0,
	RETRY,
	OPTION,
	HELP,
	MENUITEM_MAX
};

class GameMenu
{
	static C2DObject     Back;
	static UI2DAnimation Restart;
	static UI2DAnimation Retry;
	static UI2DAnimation Option;
	static UI2DAnimation Help;
	static MENUITEM      Select;
	static bool          Active;

public:
	static void Init();
	static int  Update();
	static void Draw();
	static void Uninit();

	static void Open();
	static void Close();
	static bool Check();

};

#endif // !_MENU_INCLUDE_H_
