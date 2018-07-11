#ifndef __CLASS_3D_OBJECT_BASE_H_INCLUDE__
#define __CLASS_3D_OBJECT_BASE_H_INCLUDE__

#include "LinkLibrary.h"

/* 3D�I�u�W�F�N�g��b�N���X */
class _ObjectBase3D
{
protected:
	LPDIRECT3DTEXTURE9		Texture;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;

public:
	_ObjectBase3D();

	virtual int  Init() { return 0; };
	virtual int  Update() { return 0; };
	virtual void Draw() {};
	virtual void Uninit() { this->Release(); };

	virtual void LoadTexture(const char *texture);			// �O�e�N�X�`���̓N���A(�J������)
	virtual void LoadTexture(LPDIRECT3DTEXTURE9 texture);	// �O�e�N�X�`���̓����[�X(�J���Ȃ�)
	virtual void Release();

};


/* 3D�|���S���I�u�W�F�N�g */
class C3DPolygonObject : public _ObjectBase3D
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
	C3DPolygonObject();

	virtual void Init(float posX, float posY, float posZ, float sizX, float sizY);
	virtual void Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	virtual void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size);
	virtual void Draw(void);	// �`�揈��

	virtual void LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time);
	virtual void LoadTextureStatus(float sizX, float sizY, float scale);
	virtual void LoadObjectStatus(D3DXVECTOR3 pos);
	virtual void LoadObjectStatus(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

};





#endif // !__CLASS_OBJECT_INCLUDE__
