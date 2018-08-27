//=============================================================================
//
// ��b�X�e�[�W <StageBase.h>
// Author : �� �i�V
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
	LPGimmick Onside;	// ��Q���i�\�j
	LPGimmick Ofside;	// ��Q���i���j
	LPGimmick OnBG;		// �w�i�I�u�W�F�i�\�j
	LPGimmick OfBG;		// �w�i�I�u�W�F�i���j

	string MusicPassOn;		// �\�Ȃ̃p�X
	string MusicPassOff;	// ���Ȃ̃p�X
	string BackTexOn;		// �\�w�i�̃p�X
	string BackTexOff;		// ���w�i�̃p�X
	string FieldTexOn;		// �\�̒n�ʂ̃p�X
	string FieldTexOff;		// ���̒n�ʂ̃p�X

	string NameTex;		// �X�e�[�W���e�N�X�`���̃p�X
	string ImageTex;	// �C���[�W��̃p�X
	string TestMusic;	// ���Ȃ̃p�X

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
