//=============================================================================
//
// 基礎ステージ <StageBase.cpp>
// Author : 初 景新
//
//=============================================================================
#include "StageBase.h"
#include "../Game.h"

LPGimmick::LPGimmick()
{
	Obj = NULL;
	next = NULL;
}

C3DPolygonObject *LPGimmick::Create()
{
	if (Obj == NULL)
	{// ObjがNULLのときはそこに生成
		return Obj = new C3DPolygonObject;
	}
	if (next != NULL)
	{// next先がある場合は次を呼ぶ
		return next->Create();
	}
	next = new LPGimmick;	// 新LPを作成
	return next->Obj = new C3DPolygonObject;	// そこのObjに生成
}

void LPGimmick::DrawAll()
{
	if (Obj != NULL)
	{
		Obj->Draw();
	}
	if (next != NULL)
	{
		next->DrawAll();
	}
}

void LPGimmick::DeleteAll()
{
	if (Obj != NULL)
	{
		Obj->ReleaseVertex();
		delete Obj;
		Obj = NULL;
	}
	if (next != NULL)
	{
		next->DeleteAll();
		delete next;
		next = NULL;
	}
}


int  _StageBase::Init()
{
	return 0;
}
int  _StageBase::Update()
{
	return 0;
}
void _StageBase::Draw()
{

}
void _StageBase::Uninit()
{

}
void _StageBase::SetGimmick(C3DPolygonObject *obj, int timing, int gimmick)
{

}


void _StageBase::SetNotesData(SNotes *notes, int num)
{
	/* ノーツデータをゲームノーツに登録 */
	GameSystem::Notes = new SNotes[num];
	for (int iCnt = 0; iCnt < num; iCnt++)
	{
		GameSystem::Notes[iCnt] = notes[iCnt];
	}

	/* ノーツデータに合わせてギミックを配置 */
	bool onSide = true;
	for (int iCnt = 0; iCnt < num; iCnt++)
	{
		if (onSide)
		{// 表
			C3DPolygonObject *obj = this->Onside.Create();
			SetGimmick(obj, notes[iCnt].Timing, notes[iCnt].Gimmick);
			onSide = false;
		}
		else
		{// 裏
			C3DPolygonObject *obj = this->Ofside.Create();
			SetGimmick(obj, notes[iCnt].Timing, notes[iCnt].Gimmick);
			onSide = true;
		}
	}
}

void _StageBase::back_Init()
{

}

void _StageBase::back_Draw(int side)
{
	if (side)
	{
		Ofside.DrawAll();
	}
	else
	{
		Onside.DrawAll();
	}
}

void _StageBase::back_Uninit()
{
	/* オブジェ(ギミック)を開放 */
	this->Onside.DeleteAll();
	this->Ofside.DeleteAll();
	this->OnBG.DeleteAll();
	this->OfBG.DeleteAll();
}


