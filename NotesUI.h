//=============================================================================
//
// �m�[�cUI�N���X <NotesUI.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _UI_NOTES_CLASS_INCLUDE_H_
#define _UI_NOTES_CLASS_INCLUDE_H_

#include "Library\ObjectBase2D.h"
#include "main.h"

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
class UICNotesLane : public C2DObject
{
public:
	UICNotesLane() {};
	~UICNotesLane() {};

	int  Init(void);
	void Uninit(void);

private:

};


class UICNotes : public C2DObject
{

public:
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	bool Active;

	UICNotes() {};
	~UICNotes() {};

	int  Init(void);
	void Update(void);
	void Uninit(void);

	void ReSet(void);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************



#endif
