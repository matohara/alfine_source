//=============================================================================
//
// ��� <Back.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "main.h"
#include "Back.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----����������--------
void BGCBackFrontA::Init(float posZ, float posX, float fX, float fY, LPDIRECT3DTEXTURE9 texture)
{
	// �������Z�b�g
	{
		this->Texture = NULL;		// �e�N�X�`���ւ̃|�C���^
		this->VtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		this->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu���W
		this->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�p�x
		this->Size = D3DXVECTOR2(0.0f, 0.0f);			// �|���S���T�C�Y
		this->Scale = 1.0f;								// �T�C�Y�{��
		this->TexPattern_X = 1;		// �e�N�X�`���p�^�[���i���j
		this->TexPattern_Y = 1;		// �e�N�X�`���p�^�[���i�c�j
		this->AnimeCount = 0;		// �A�j���[�V�����J�E���g
		this->AnimePattern = 0;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
		this->ChangeAnimeTime = 0;	// �A�j���[�V�����؂�ւ��Ҏ���
	}

	// ��{���Z�b�g
	this->Size = { fX, fY };
	this->Position.z = posZ;
	this->Position.x = posX;

	// �e�N�X�`���ǂݍ���
	this->LoadTexture(texture);

	// ���_�ݒ�
	this->MakeVertex();
	this->SetVertex();
}

//----�I������--------
void BGCBackFrontA::Uninit(void)
{

}

//----���_�ݒ�--------
void BGCBackFrontA::SetVertex(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-Size.x, Size.y * 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x, Size.y * 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x,          0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x,          0.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}

//----�J��--------
void BGCBackFrontA::ReleaseBuffer(void)
{
	if (this->VtxBuff != NULL)
	{
		this->VtxBuff->Release();
		this->VtxBuff = NULL;
	}
}


//----����������--------
void GameBackGround::Init(float posZ, float fX, float fY, const char *texture)
{
	this->LoadTexture(texture);
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		Parts[iCnt].Init(posZ, fX * 2.0f * iCnt, fX, fY, this->Texture);
	}
}

//----�I������--------
void GameBackGround::Uninit(void)
{
	if (Texture != NULL)
	{
		Texture->Release();
		Texture = NULL;
	}
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		Parts[iCnt].ReleaseBuffer();
	}
}

//----�`�揈��--------
void GameBackGround::Draw(void)
{
	for (int iCnt = 0; iCnt < BACK_NUM; iCnt++)
	{
		this->Parts[iCnt].Draw();
	}
}

//----�e�N�X�`���ǂݍ���--------
void GameBackGround::LoadTexture(const char *texture)
{
	if (Texture != NULL)
	{	// �e�N�X�`���̊J��
		Texture->Release();
		Texture = NULL;
	}
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}

