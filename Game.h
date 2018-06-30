//=============================================================================
//
// ゲーム画面処理 [Game.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _GAME_INCLUDE_H_
#define _GAME_INCLUDE_H_

#include "main.h"
#include "sound.h"

#include "source/class/ObjectBase.h"
#include "source/object/Player.h"
#include "Back.h"
#include "Field.h"

#include "GuideUI.h"
#include "NotesUI.h"
#include "HPUI.h"
#include "StatusBarUI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
/* General */

/* GameFlag */
#define FLAG_GAME_PLAYING   (0x80000000)	// ゲーム中かどうか
#define FLAG_GAME_MAPSIDES  (0x00000001)	// 現在の表裏 (0:表, 1:裏)
#define FLAG_GAME_NEXTSIDES (0x00000002)	// 次になるべき表裏 (0:表, 1:裏)
#define FLAG_GAME_   (0x00000000)
#define FLAG_GAME_INIT      (FLAG_GAME_NEXTSIDES)

/* SoundVolume */
#define VOLUME_MAX (DSBVOLUME_MAX)
#define VOLUME_MIN (DSBVOLUME_MIN)

/* Color */
#define GAMECOLOR_RED D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f)


enum FLAGTYPE
{
	FT_CHANGE = -1,
	FT_OR,
	FT_DELETE,
	FT_UPDATE,
	FT_CHECK,
	FT_MAX
};

//*****************************************************************************
// クラス設計
//*****************************************************************************
class CNotes
{
public:
	int Timing;

	CNotes()
	{
		Timing = 0;
	};
	CNotes(int time)
	{
		Timing = time;
	};
	~CNotes()
	{

	};

private:

};

class GameSystem
{
public:
	PlayerB TestPlayer;
	CNotes *Notes;
	FieldA TestField[3];
	BGCBackFront BackWall[3];
	BGCBackFront FrontWall[3];

	C2DUIPolygon BackPolyUI;
	C2DUIPolygon LogoOption;
	UICGuide GuideUI;
	UICHitPoint HitPointUI;
	UICNvX NumberSlashMAX;

	UINT GameFlag;

	int GameCounter;
	int NotesCounter;
	int NotesCounter2;
	int PlayerHP;

public:
	GameSystem() {};
	~GameSystem() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void CallGuideUI(D3DXVECTOR3 pos);

private:

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
UINT SetGameFlag(UINT flg, FLAGTYPE type);

int GetPlayerHP(void);

#ifdef _DEBUG
int CallNotesUI(void);
#endif

#endif
