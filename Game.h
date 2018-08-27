//=============================================================================
//
// �Q�[����ʏ��� [Game.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _GAME_INCLUDE_H_
#define _GAME_INCLUDE_H_

#include "main.h"
#include "Stage.h"

#include "Library\Counter.h"
#include "Library\Sound.h"
#include "Library\ObjectBase3D.h"
#include "Library\ObjectBase2D.h"
#include "Player.h"
#include "Back.h"
#include "Field.h"
#include "Notes.h"

#include "GuideUI.h"
#include "NotesUI.h"
#include "HPUI.h"
#include "StatusBarUI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
/* General */

/* GameFlag */
#define FLAG_GAME_PLAYING   (0x80000000)	// �Q�[�������ǂ���
#define FLAG_GAME_MAPSIDES  (0x00000001)	// ���݂̕\�� (0:�\, 1:��)
#define FLAG_GAME_NEXTSIDES (0x00000002)	// ���ɂȂ�ׂ��\�� (0:�\, 1:��)
#define FLAG_GAME_MENU      (0x40000000)	// ���j���[��ʂ��J���Ă��邩
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
// �N���X�݌v
//*****************************************************************************
class GameSystem
{
public:
	static StageBase *Stage;
	static DSound BackMusic[2];

	static PlayerB MainPlayer;
	static SNotes *Notes;

	static GameField      OnSideField;
	static GameField      OffSideField;
	static GameBackGround OnSideBG;
	static GameBackGround OffSideBG;

	static CountDown   Countdown;
	static C2DObject   BackPolyUI;
	static C2DObject   LogoOption;
	static UICGuide    GuideUI;
	static UICHitPoint HitPointUI;

	static UINT GameFlag;
	static int  GameCounter;
	static int  NotesCounter;
	static int  NotesCounter2;
	static int  PlayerHP;

public:
	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);

	static void CallGuideUI(D3DXVECTOR3 pos);

private:
	GameSystem() {};

};


//*****************************************************************************
// �v���g�^�C�v�錾
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
