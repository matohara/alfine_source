//=============================================================================
//
// 基礎ステージ <StageBase.h>
// Author : 初 景新
//
//=============================================================================
#ifndef _STAGE_BASE_H_INCLUDE_
#define _STAGE_BASE_H_INCLUDE_

#include "../Library/ObjectBase2D.h"
#include "../Library/ObjectBase3D.h"
#include "../Notes.h"
#include <string>

using namespace std;

class LPGimmick
{
	LPGimmick *next;
public:
	C3DPolygonObject *Obj;

	LPGimmick();
	C3DPolygonObject *Create();
	void DrawAll();
	void DeleteAll();

};

typedef class _StageBase
{

public:
	LPGimmick Onside;	// 障害物（表）
	LPGimmick Ofside;	// 障害物（裏）
	LPGimmick OnBG;		// 背景オブジェ（表）
	LPGimmick OfBG;		// 背景オブジェ（裏）

	string MusicPassOn;		// 表曲のパス
	string MusicPassOff;	// 裏曲のパス
	string BackTexOn;		// 表背景のパス
	string BackTexOff;		// 裏背景のパス
	string FieldTexOn;		// 表の地面のパス
	string FieldTexOff;		// 裏の地面のパス

	string NameTex;		// ステージ名テクスチャのパス
	string ImageTex;	// イメージ画のパス
	string TestMusic;	// 試曲のパス

public:
	virtual int  Init();
	virtual int  Update();
	virtual void Draw();
	virtual void Uninit();
	virtual void SetGimmick(C3DPolygonObject *obj, int timing, int gimmick);

	void SetNotesData(SNotes *notes, int num);
	void back_Init();
	void back_Draw(int side);
	void back_Uninit();

}StageBase;



#endif // !_STAGE_BASE_H_INCLUDE_
