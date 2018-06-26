//=============================================================================
//
// ��� <Back.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef _BACK_INCLUDE_H_
#define _BACK_INCLUDE_H_

#include "source/class/Aclass_object.h"

// �}�N����`
#define TEXTURE_FILE_BACK_B  "data/STAGE/BackTextureB.txt"
#define TEXTURE_FILE_BACK_F  "data/STAGE/BackTextureF.txt"

#define TEXTURE_GAME_1F_BACK	_T("data/TEXTURE/�`���[�g���A��/Back111.jpg")
#define TEXTURE_GAME_1F_FRONT	_T("data/TEXTURE/�`���[�g���A��/Back112.png")

#define TEXTURE_GAME_2F_BACK	_T("data/TEXTURE/�`���[�g���A��/Back211.jpg")
#define TEXTURE_GAME_2F_FRONT	_T("data/TEXTURE/�`���[�g���A��/Back212.png")

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class BGCBackFront : public class_ObjectA
{
	LPDIRECT3DTEXTURE9 *BackTexture[2];
	int MapMax;

public:
	BGCBackFront() {};
	~BGCBackFront() {};

	void Init(float posZ, float fX, float fY, const char *file, int posX);
	void Update(void);
	void Draw(int sides, int map);
	void Uninit(void);

	void LoadTexture(const char *file);

	void SetVertex(void);

private:

};



#endif
