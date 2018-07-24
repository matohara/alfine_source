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
#include "../Game.h"

class LP3DPorygonObject
{
	LP3DPorygonObject *next;
public:
	C3DPolygonObject *Obj;

	LP3DPorygonObject();
	C3DPolygonObject *Create();
	void DrawAll();
	void DeleteAll();

};

typedef class _StageBase
{
	LP3DPorygonObject Onside;
	LP3DPorygonObject Ofside;
public:
	int  Init();
	int  Update();
	void Draw();
	void Uninit();

	void back_Draw(int side);

}StageBase;



#endif // !_STAGE_BASE_H_INCLUDE_
