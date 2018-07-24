//=============================================================================
//
// ÉÅÉjÉÖÅ[èàóù <Menu.cpp>
// Author : èâ åiêV
//
//=============================================================================
#include "Menu.h"
#include "Library\Input.h"
#include "Library\Fade.h"


#define GAMEMENU_TEX_BACK    "data/TEXTURE/UI/OptionFrame.png"
#define GAMEMENU_TEX_RESTART "data/TEXTURE/UI/MENU/Option_G00.png"
#define GAMEMENU_TEX_RETRY   "data/TEXTURE/UI/MENU/Option_G01.png"
#define GAMEMENU_TEX_OPTION  "data/TEXTURE/UI/MENU/Option_G02.png"
#define GAMEMENU_TEX_HELP    "data/TEXTURE/UI/MENU/Option_G03.png"


C2DObject     GameMenu::Back;
UI2DAnimation GameMenu::Restart;
UI2DAnimation GameMenu::Retry;
UI2DAnimation GameMenu::Option;
UI2DAnimation GameMenu::Help;
MENUITEM      GameMenu::Select = RESTART;
bool          GameMenu::Active = false;

void GameMenu::Init()
{
	Back.Init(    SCREEN_CENTER_X,  SCREEN_CENTER_Y, 250, 350, GAMEMENU_TEX_BACK    );
	Restart.Init( SCREEN_CENTER_X, RelativeSY(0.2f), 100,  50, GAMEMENU_TEX_RESTART );
	Retry.Init(   SCREEN_CENTER_X, RelativeSY(0.4f), 100,  50, GAMEMENU_TEX_RETRY   );
	Option.Init(  SCREEN_CENTER_X, RelativeSY(0.6f), 100,  50, GAMEMENU_TEX_OPTION  );
	Help.Init(    SCREEN_CENTER_X, RelativeSY(0.8f), 100,  50, GAMEMENU_TEX_HELP    );
	Select = RESTART;
	Active = false;
}

void GameMenu::Open()
{
	Active = true;
	Select = RESTART;
}

void GameMenu::Close()
{
	Active = false;
}

int GameMenu::Update()
{
	if (Active)
	{
		if (GetKeyboardTrigger(DIK_UP))
		{
			Select = (MENUITEM)((int)(Select - 1 + (int)MENUITEM_MAX) % (int)MENUITEM_MAX);
		}
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			Select = (MENUITEM)((int)(Select + 1) % (int)MENUITEM_MAX);
		}
		switch (Select)
		{
		case RESTART:
			Help.ResetData(0);
			Restart.Animation01();
			Retry.ResetData(0);
			if (GetKeyboardTrigger(DIK_RETURN))
				return 1;
			break;
		case RETRY:
			Restart.ResetData(0);
			Retry.Animation01();
			Option.ResetData(0);
			if (GetKeyboardTrigger(DIK_RETURN))
				CSFade::SetFade(SCENE_GAME);
			break;
		case OPTION:
			Retry.ResetData(0);
			Option.Animation01();
			Help.ResetData(0);
			if (GetKeyboardTrigger(DIK_RETURN))
				return 0;
			break;
		case HELP:
			Option.ResetData(0);
			Help.Animation01();
			Restart.ResetData(0);
			if (GetKeyboardTrigger(DIK_RETURN))
				return 0;
			break;
		}
	}
	return 0;
}

void GameMenu::Draw()
{
	if (Active)
	{
		Back.Draw();
		Restart.Draw();
		Retry.Draw();
		Option.Draw();
		Help.Draw();
	}
}

void GameMenu::Uninit()
{
	Back.Release();
	Restart.Release();
	Retry.Release();
	Option.Release();
	Help.Release();
}

bool GameMenu::Check()
{
	return Active;
}


