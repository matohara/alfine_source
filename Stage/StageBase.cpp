//=============================================================================
//
// ��b�X�e�[�W <StageBase.cpp>
// Author : �� �i�V
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
	{// Obj��NULL�̂Ƃ��͂����ɐ���
		return Obj = new C3DPolygonObject;
	}
	if (next != NULL)
	{// next�悪����ꍇ�͎����Ă�
		return next->Create();
	}
	next = new LPGimmick;	// �VLP���쐬
	return next->Obj = new C3DPolygonObject;	// ������Obj�ɐ���
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
	/* �m�[�c�f�[�^���Q�[���m�[�c�ɓo�^ */
	GameSystem::Notes = new SNotes[num];
	for (int iCnt = 0; iCnt < num; iCnt++)
	{
		GameSystem::Notes[iCnt] = notes[iCnt];
	}

	/* �m�[�c�f�[�^�ɍ��킹�ăM�~�b�N��z�u */
	bool onSide = true;
	for (int iCnt = 0; iCnt < num; iCnt++)
	{
		if (onSide)
		{// �\
			C3DPolygonObject *obj = this->Onside.Create();
			SetGimmick(obj, notes[iCnt].Timing, notes[iCnt].Gimmick);
			onSide = false;
		}
		else
		{// ��
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
	/* �I�u�W�F(�M�~�b�N)���J�� */
	this->Onside.DeleteAll();
	this->Ofside.DeleteAll();
	this->OnBG.DeleteAll();
	this->OfBG.DeleteAll();
}


