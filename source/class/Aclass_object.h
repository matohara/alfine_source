//=============================================================================
//
// Object-AClass <object.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef __CLASS_OBJECT_CLASS_INCLUDE_H__
#define __CLASS_OBJECT_CLASS_INCLUDE_H__


#include "../../main.h"
#include "../../Camera.h"

using namespace std;

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
/* ��{�N���X */
class c3DBasicObjectClass
{

protected:
	LPDIRECT3DTEXTURE9		Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	c3DBasicObjectClass();
	~c3DBasicObjectClass();

//	virtual void Draw(void);						// �`�揈��
//	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�e�N�X�`���w��)

	virtual void LoadTexture(const char *texture);
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);

private:

};


/* �I�u�W�F�N�gA�N���X */
class class_ObjectA : public c3DBasicObjectClass
{

protected:
	D3DXVECTOR3 Position;	// �ʒu���W
	D3DXVECTOR3 Rotation;	// ��]�p�x
	D3DXVECTOR2 Size;		// �|���S���T�C�Y
	float Scale;			// �T�C�Y�{��

	int TexPattern_X;		// �e�N�X�`���p�^�[���i���j
	int TexPattern_Y;		// �e�N�X�`���p�^�[���i�c�j
	int AnimeCount;			// �A�j���[�V�����J�E���g
	int AnimePattern;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	int ChangeAnimeTime;	// �A�j���[�V�����؂�ւ��Ҏ���

	virtual int MakeVertex(void);
	virtual void SetVertex(void);				// ���_���W�ݒ�@���_�ʒu�̂�
	virtual void SetVertex(D3DXCOLOR color);	// ���_���W�ݒ�@���_�F����

public:
	class_ObjectA();
	~class_ObjectA();

	virtual void Draw(void);						// �`�揈��
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�e�N�X�`���w��)
	virtual void DrawBillboard(void);						// �`�揈��(�r���{�[�h)
	virtual void DrawBillboard(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�r���{�[�h)(�e�N�X�`���w��)

	virtual void ReleaseBuffer(void);	// �o�b�t�@�n�J��
	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);	//�e�N�X�`�����@�A�j���[�V�����Ȃ�

	virtual void FlipX(void);	// ���E���]

private:

};


/* �I�u�W�F�N�gP�N���X */
class class_ObjectP : public c3DBasicObjectClass
{
public:
	class_ObjectP();
	~class_ObjectP();

//	virtual int MakeVertex(D3DXVECTOR3 size, D3DXVECTOR3 nor);
	virtual void SetVertex(float sizeX, float sizeY);

private:

};


/* �I�u�W�F�N�gU�N���X */
class class_ObjectU
{
	
protected:
	LPDIRECT3DTEXTURE9	Texture;	// �e�N�X�`���ւ̃|�C���^

	virtual void MakeVertex(float sizeX, float sizeY, float posX, float posY);	// ���_�쐬
	virtual void MakeVertex(float sizeX, float sizeY);

public:
	VERTEX_2D	Vertex[NUM_VERTEX];	// ���_���

	class_ObjectU();
	~class_ObjectU();

	virtual void Draw(void);						// �`�揈��(�ʏ�)
	virtual void Draw(LPDIRECT3DTEXTURE9 texture);	// �`�揈��(�ʏ�)(�e�N�X�`���w��)

	virtual void ReleaseBuffer(void);	// �o�b�t�@�n�J��
	virtual void LoadTexture(const char *texture);
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);

	virtual void SetVertex(float sizeX, float sizeY, float posX, float posY);	// ���_���W�ݒ�
	virtual void SetVertex(float sizeX, float sizeY);
	virtual void SetVertex(D3DXCOLOR color);

	virtual void SetPosition(float posX, float posY);	// �ړ�
	virtual void SetTexture(int num, int ix, int iy);	// �e�N�X�`�����W�ݒ�

	virtual LPDIRECT3DTEXTURE9 GetTextureAddress(LPDIRECT3DTEXTURE9 *texture);

private:

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
