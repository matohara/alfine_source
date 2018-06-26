//=============================================================================
//
// �w�i���� [bg.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _BG_INCLUDE_H_
#define _BG_INCLUDE_H_

#include "source/class/Aclass_object.h"

// �}�N����`
#define TEXTURE_GAME_BG	_T("data/TEXTURE/FIELD/BG.jpg")	// �T���v���p�摜
#define BG_SIZE_X		(2000)	// �e�N�X�`���T�C�Y
#define BG_SIZE_Y		(2000)	// ����
#define BG_POS_X		(0)		// �|���S���̏����ʒuX
#define BG_POS_Y		(0)		// ����

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class CBackTexture : public class_ObjectA
{
public:
	CBackTexture() {};
	~CBackTexture() {};

	void SetBGTStatus(float fX, float fY, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif
