//=============================================================================
//
// �n�ʃN���X <Field.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "Field.h"


#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"


//----����������--------
void FieldA::Init(float posX, float sizeX, float sizeY, LPDIRECT3DTEXTURE9 texture)
{
	// �f�[�^�̏�����
	this->Texture = NULL;
	this->Position = D3DXVECTOR3(posX, 0.0f, 0.0f);
	this->Rotation = D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f);

	this->LoadTexture(texture);						// �e�N�X�`���ǂݍ���
	this->LoadTextureStatus(sizeX, sizeY, 1.0f);	// �����Z�b�g
	this->MakeVertex();								// ���_�쐬
}


//----����������--------
void GameField::Init(float sizeX, float sizeY, const char *texture)
{
	this->LoadTexture(texture);
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Init(sizeX * 2.0f * iCnt, sizeX, sizeY, Texture);
	}
}

//----�`�揈��--------
void GameField::Draw()
{
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Draw();
	}
}

//----�I������--------
void GameField::Uninit()
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	for (int iCnt = 0; iCnt < FIELD_MUN; iCnt++)
	{
		Parts[iCnt].Release();
	}
}

//----�e�N�X�`����^����--------
void GameField::LoadTexture(const char *texture)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}

