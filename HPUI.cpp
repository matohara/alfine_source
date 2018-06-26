//=============================================================================
//
// HPUI�N���X <HPUI.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "HPUI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----����������--------
void UICHitPoint::Init(int num, float sizeX, float sizeY, float posX, float posY)
{
	// �e�N�X�`��
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP01, &Texture[0]);
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP02, &Texture[1]);

	HP_MAX = num;
	HP_UI = new C2DUIPolygon[HP_MAX];

	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		HP_UI[iCnt].Init(sizeX, sizeY, posX + sizeX * 2 * (iCnt - (HP_MAX / 2)), posY);
	}
}
void UICHitPoint::Init(int num)
{
	// �e�N�X�`��
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP01, &Texture[0]);
	D3DXCreateTextureFromFile(GetDevice(), UI_TEX_HP02, &Texture[1]);

	HP_MAX = num;
	HP_UI = new C2DUIPolygon[HP_MAX];

	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		HP_UI[iCnt].Init(HPUI_SIZE_X, HPUI_SIZE_Y, HPUI_POS_X * (float)(iCnt+1), HPUI_POS_Y);
	}
}

//----�X�V--------
void UICHitPoint::Update(void)
{

}

//----�`�揈��--------
void UICHitPoint::Draw(int hp)
{
	for (int iCnt = 0; iCnt < HP_MAX; iCnt++)
	{
		if (hp > 0)
		{
			HP_UI[iCnt].Draw(Texture[0]);
		}
		else
		{
			HP_UI[iCnt].Draw(Texture[1]);
		}
		hp--;
	}
}

//----�I������--------
void UICHitPoint::Uninit(void)
{
	delete[] HP_UI;

	if (Texture[0] != NULL)
	{
		Texture[0]->Release();
		Texture[0] = NULL;
	}
	if (Texture[1] != NULL)
	{
		Texture[1]->Release();
		Texture[1] = NULL;
	}
}


