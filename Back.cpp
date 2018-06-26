//============================================================================
//
// ��� <Back.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "main.h"
#include "Back.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----�e�N�X�`�������[�h--------
void BGCBackFront::LoadTexture(const char *file)
{
	// Output �󂯎��
	FILE *fp = fopen(file, "r");	// �t�@�C�����J��

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
	BackTexture[0] = new LPDIRECT3DTEXTURE9[MapMax];
	BackTexture[1] = new LPDIRECT3DTEXTURE9[MapMax];

	// �t�@�C���p�X��ǂݍ���
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#BACK_TEXTURE"))
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
		D3DXCreateTextureFromFile(pDevice, pass, &BackTexture[0][iCnt]);
		// ���e�N�X�`���ǂݍ���
		fscanf(fp, "%s", pass);
		D3DXCreateTextureFromFile(pDevice, pass, &BackTexture[1][iCnt]);
	}

	fclose(fp);	// �t�@�C������I��

}

//----����������--------
void BGCBackFront::Init(float posZ, float fX, float fY, const char *file, int posX)
{
	// �������Z�b�g
	{
		Texture = NULL;		// �e�N�X�`���ւ̃|�C���^
		VtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu���W
		Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�p�x
		Size = D3DXVECTOR2(0.0f, 0.0f);				// �|���S���T�C�Y
		Scale = 1.0f;								// �T�C�Y�{��
		TexPattern_X = 1;		// �e�N�X�`���p�^�[���i���j
		TexPattern_Y = 1;		// �e�N�X�`���p�^�[���i�c�j
		AnimeCount = 0;			// �A�j���[�V�����J�E���g
		AnimePattern = 0;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
		ChangeAnimeTime = 0;	// �A�j���[�V�����؂�ւ��Ҏ���
	}

	// ��{���Z�b�g
	Size = { fX, fY };
	Position.x = fX * 2 * posX;
	Position.z = posZ;

	// �e�N�X�`���ǂݍ���
	LoadTexture(file);

	// ���_�ݒ�
	MakeVertex();
	SetVertex();
}

//----�I������--------
void BGCBackFront::Uninit(void)
{
	this->class_ObjectA::ReleaseBuffer();

	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		if (BackTexture[0][iCnt] != NULL)
		{
			BackTexture[0][iCnt]->Release();
			BackTexture[0][iCnt] = NULL;
		}
		if (BackTexture[1][iCnt] != NULL)
		{
			BackTexture[1][iCnt]->Release();
			BackTexture[1][iCnt] = NULL;
		}
	}
	delete[] BackTexture[0];
	delete[] BackTexture[1];
	BackTexture[0] = NULL;
	BackTexture[1] = NULL;

}

//----�X�V����--------
void BGCBackFront::Update(void)
{

}

//----�`�揈��--------
void BGCBackFront::Draw(int sides, int map)
{
	this->class_ObjectA::DrawBillboard(BackTexture[sides][map]);
}


//----���_�ݒ�--------
void BGCBackFront::SetVertex(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x, Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, 0.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}

