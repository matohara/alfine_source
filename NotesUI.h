//=============================================================================
//
// ノーツUIクラス <NotesUI.h>
// Author : 初 景新
//
//=============================================================================
#ifndef _UI_NOTES_CLASS_INCLUDE_H_
#define _UI_NOTES_CLASS_INCLUDE_H_

#include "Library\ObjectBase2D.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_TEX_NOTES  "data/TEXTURE/UI/Notes.png"
#define UI_TEX_LANE   "data/TEXTURE/UI/LaneUI.png"

#define NOTES_SIZE_X	(15)
#define NOTES_SIZE_Y	(30)

//*****************************************************************************
// クラス設計
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
// プロトタイプ宣言
//*****************************************************************************



#endif
