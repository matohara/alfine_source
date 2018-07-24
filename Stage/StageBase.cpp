//=============================================================================
//
// ��b�X�e�[�W <StageBase.cpp>
// Author : �� �i�V
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
	{// Obj��NULL�̂Ƃ��͂����ɐ���
		return Obj = new C3DPolygonObject;
	}
	if (next != NULL)
	{// next�悪����ꍇ�͎����Ă�
		return next->Create();
	}
	next = new LP3DPorygonObject;	// �VLP���쐬
	return next->Obj = new C3DPolygonObject;	// ������Obj�ɐ���
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



