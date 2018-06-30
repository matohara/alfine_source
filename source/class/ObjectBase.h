//=============================================================================
//
// Object-Base <object.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef __CLASS_OBJECT_BASE_INCLUDE_H__
#define __CLASS_OBJECT_BASE_INCLUDE_H__

#include "Aclass_object.h"

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
/* �I�u�W�F�N�gA�N���X */
class C3DPolygonObject : public class_ObjectA
{
public:
	void Init(D3DXVECTOR3 pos, float fX, float fY);
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fX, float fY);
	void Init(D3DXVECTOR3 pos, float fX, float fY, const char *file);
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fX, float fY, const char *file);
//	void Animation(void);
	int HitCheck(D3DXVECTOR3 pos);

private:

};

/* �����̃I�u�W�F�N�g* */
class C3DCubeObject : public class_ObjectP
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Size;
	D3DXVECTOR3 Rotation;

public:
	C3DCubeObject() {};
	~C3DCubeObject() {};

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, const char *tex);
//	int MakeVertex(D3DXVECTOR3 size, D3DXVECTOR3 nor);

private:

};


/* �I�u�W�F�N�gG�N���X */


/* �I�u�W�F�N�gU�N���X */
class C2DUIPolygon : public class_ObjectU
{
public:
	virtual void Init(float sizeX, float sizeY, float posX, float posY, const char *texture);
	virtual void Init(float sizeX, float sizeY, float posX, float posY);
	virtual void Init(float sizeX, float sizeY, const char *texture);
	virtual void Init(const char *texture);
	virtual void Init(void);

private:

};

class C2DUIPolygonA : public C2DUIPolygon
{
	int TexPattern_X;		// �e�N�X�`���p�^�[���i���j
	int TexPattern_Y;		// �e�N�X�`���p�^�[���i�c�j
	int AnimeCount;			// �A�j���[�V�����J�E���g
	int AnimePattern;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	int ChangeAnimeTime;	// �A�j���[�V�����؂�ւ��Ҏ���

public:
	C2DUIPolygonA();

	void Animation(void);

private:

};

class C2DUIMenuLogo : public C2DUIPolygon
{
<<<<<<< HEAD

public:
=======
public:

>>>>>>> 3d1d2c42f701a0751764c57f7c58b2e3bfe651f9
	D3DXCOLOR Color;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	float Scale;
	float Curve;
	float Open;

public:
	C2DUIMenuLogo();

	void Init(float sizeX, float sizeY, float posX, float posY, const char *texture);
	void Init(float sizeX, float sizeY, float posX, float posY);
	void Init(float sizeX, float sizeY);
	void ReSet(void);

	void Animation01(void);
	void Animation02(void);
	void Animation03(void);
	void Open01(void);
	void Close01(void);

private:

};

class C2DUINumber : public C2DUIPolygon
{
public:
	void SetNumber(int num);

private:

};

class C2DUIPercentGauge
{
	D3DXVECTOR2 Size;
	D3DXVECTOR2 Position;

public:
	C2DUIPolygonA Frame;
	C2DUIPolygonA Gage;

	void Init(const char *textureF, const char *textureG);
	void Init(float sizeX, float sizeY, float posX, float posY);
	void Update(float per);
	void Draw(void);
	void Uninit(void);

private:

};



#endif
