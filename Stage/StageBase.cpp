//=============================================================================
//
// 基礎ステージ <StageBase.cpp>
// Author : 初 景新
//
//=============================================================================
#include "StageBase.h"


LP3DPorygonObject::LP3DPorygonObject()
{
	next = NULL;
	Obj = NULL;
}

C3DPolygonObject *LP3DPorygonObject::Create()
{
	if (Obj == NULL)
	{// ObjがNULLのときはそこに生成
		return Obj = new C3DPolygonObject;
	}
	if (next != NULL)
	{// next先がある場合は次を呼ぶ
		return next->Create();
	}
	next = new LP3DPorygonObject;	// 新LPを作成
	return next->Obj = new C3DPolygonObject;	// そこのObjに生成
}

void LP3DPorygonObject::DrawAll()
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

void LP3DPorygonObject::DeleteAll()
{
	if (Obj != NULL)
	{
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



