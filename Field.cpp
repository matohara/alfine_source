//=============================================================================
//
// �n�ʃN���X <Field.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "input.h"
#include "Field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FILE_FIELD  "data/STAGE/FieldTexture.txt"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----�e�N�X�`�������[�h--------
void FieldA::LoadTexture(void)
{
	// Output �󂯎��
	FILE *fp = fopen(TEXTURE_FILE_FIELD, "r");	// �t�@�C�����J��

	if (fp == NULL)
	{// �t�@�C�����J�������`�F�b�N
		MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Open\"", MB_YESNO);
	}

	// �}�b�v�f�[�^�����
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#MAP_NUMBER"))
		{
			MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Read\"", MB_YESNO);
		}
	}

	// �������m��
	fscanf(fp, "%d", &MapMax);
	FieldTexture[0] = new LPDIRECT3DTEXTURE9[MapMax];
	FieldTexture[1] = new LPDIRECT3DTEXTURE9[MapMax];

	// �t�@�C���p�X��ǂݍ���
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#FIELD_TEXTURE"))
		{
			MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// �e�N�X�`���ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char pass[256];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		// �\�e�N�X�`���ǂݍ���
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &FieldTexture[0][iCnt]);
		// ���e�N�X�`���ǂݍ���
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &FieldTexture[1][iCnt]);
	}

	fclose(fp);	// �t�@�C������I��

}

//----�����Z�b�g--------
void FieldA::LoadStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f);

	MakeVertex();
}


//----����������--------
void FieldA::Init(float x, float y, int posX)
{
	// �f�[�^�̏�����
	FieldTexture[0] = NULL;
	FieldTexture[1] = NULL;
	MapMax = 0;

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f);
	Position.x = x * 2 * posX;

	// �e�N�X�`���ǂݍ���
	//if (posX == 0)
	{
		LoadTexture();
	}

	// �����Z�b�g
	LoadStatus(x, y);
}

//----�X�V--------
void FieldA::Update(void)
{

}

//----�`�揈��--------
void FieldA::Draw(int sides, int map)
{
	this->class_ObjectA::Draw(FieldTexture[sides][map]);
}

//----�I������--------
void FieldA::Uninit(void)
{
	// �o�b�t�@�J��
	this->FieldA::ReleaseBuffer();
	this->class_ObjectA::ReleaseBuffer();
}


//----�o�b�t�@�J��--------
void FieldA::ReleaseBuffer(void)
{
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		if (FieldTexture[0][iCnt] != NULL)
		{
			FieldTexture[0][iCnt]->Release();
			FieldTexture[0][iCnt] = NULL;
		}
		if (FieldTexture[1][iCnt] != NULL)
		{
			FieldTexture[1][iCnt]->Release();
			FieldTexture[1][iCnt] = NULL;
		}
	}
	delete[] FieldTexture[0];
	delete[] FieldTexture[1];

	FieldTexture[0] = NULL;
	FieldTexture[1] = NULL;
}

