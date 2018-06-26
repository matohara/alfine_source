//=============================================================================
//
// �m�[�cUI�N���X <NotesUI.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _UI_NOTES_CLASS_INCLUDE_H_
#define _UI_NOTES_CLASS_INCLUDE_H_

#include "main.h"
#include "source/class/Aclass_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_TEX_NOTES  "data/TEXTURE/UI/Notes.png"
#define UI_TEX_LANE   "data/TEXTURE/UI/LaneUI.png"

#define NOTES_SIZE_X	(15)
#define NOTES_SIZE_Y	(30)

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class UICNotesLane : public class_ObjectU
{
public:
	UICNotesLane() {};
	~UICNotesLane() {};

	void Init(void);
//	void Update(void);
	void Draw(void);
	void Uninit(void);

private:

};


class UICNotes : public class_ObjectU
{

public:
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	bool Active;

	UICNotes() {};
	~UICNotes() {};

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	void ReSet(void);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



#endif
