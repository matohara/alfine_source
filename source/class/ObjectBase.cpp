//=============================================================================
//
// Object-Base <object.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "ObjectBase.h"


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//=============================================================================
// < A�^��ʃI�u�W�F�N�g >
//=============================================================================

/* 3D �ėp�|���S�� */
//----������--------
void C3DPolygonObject::Init(D3DXVECTOR3 pos, float fX, float fY, const char *file)
{
	// ��{���Z�b�g
	Size = { fX, fY };
	Position = pos;

	// �e�N�X�`���ǂݍ���
	LoadTexture(file);

	// ���_�ݒ�
	MakeVertex();
}
void C3DPolygonObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fX, float fY, const char *file)
{
	// ��{���Z�b�g
	Size = { fX, fY };
	Position = pos;
	Rotation = rot;

	// �e�N�X�`���ǂݍ���
	this->class_ObjectA::LoadTexture(file);

	// ���_�ݒ�
	this->class_ObjectA::MakeVertex();
}

//=============================================================================
// < G�^��ʃI�u�W�F�N�g >
//=============================================================================


//=============================================================================
// < U�^��ʃI�u�W�F�N�g >
//=============================================================================

/* 2DUI �ėp�|���S�� */
//----����������--------
void C2DUIPolygon::Init(float sizeX, float sizeY, float posX, float posY, const char *texture)
{
	this->LoadTexture(texture);

	this->MakeVertex(sizeX, sizeY, posX, posY);
}
void C2DUIPolygon::Init(float sizeX, float sizeY, float posX, float posY)
{
	this->MakeVertex(sizeX, sizeY, posX, posY);
}
void C2DUIPolygon::Init(float sizeX, float sizeY, const char *texture)
{
	this->LoadTexture(texture);

	this->MakeVertex(sizeX, sizeY, SCREEN_CENTER_X, SCREEN_CENTER_Y);
}
void C2DUIPolygon::Init(const char *texture)
{
	this->LoadTexture(texture);
	this->MakeVertex(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
}
void C2DUIPolygon::Init(void)
{
	this->MakeVertex(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	this->SetVertex(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
}


/* 2DUI �A�j���[�V�����\�ėp�|���S�� */
//----�R���X�g���N�^--------
C2DUIPolygonA::C2DUIPolygonA()
{
	TexPattern_X;
	TexPattern_Y;
	AnimeCount;
	AnimePattern;
	ChangeAnimeTime;
}

//----�A�j���[�V����--------
void C2DUIPolygonA::Animation(void)
{
	if ((TexPattern_X * TexPattern_Y) > 1)// �e�N�X�`����ނ����̏ꍇ�̓X�L�b�v
	{
		/* �A�j���[�V���� */
		AnimeCount++;
		if ((AnimeCount % ChangeAnimeTime) == 0)
		{
			// �p�^�[���̐؂�ւ�
			AnimePattern = (AnimePattern + 1) % (TexPattern_X * TexPattern_Y);
		}

		// �e�N�X�`�����W�̐ݒ�
		int x = AnimePattern % TexPattern_X;
		int y = AnimePattern / TexPattern_X;
		float sizeX = 1.0f / TexPattern_X;
		float sizeY = 1.0f / TexPattern_Y;

		this->Vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		this->Vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		this->Vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		this->Vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
}


/* 2DUI �����\���|���S�� */
//----�\�������ݒ�--------
void C2DUINumber::SetNumber(int num)
{
	this->SetTexture(num, 10, 1);
}


/* 2DUI ���j���[���S�pUI */
//----�R���X�g���N�^--------
C2DUIMenuLogo::C2DUIMenuLogo()
{
	Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Position = D3DXVECTOR2(0.0f, 0.0f);
	Size = D3DXVECTOR2(100.0f, 100.0f);
	Scale = 0.0f;
	Curve = 0.0f;
	Open = 0.0f;
}

//----������--------
void C2DUIMenuLogo::Init(float sizeX, float sizeY, float posX, float posY, const char *texture)
{
	{
		Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Position = D3DXVECTOR2(0.0f, 0.0f);
		Size = D3DXVECTOR2(100.0f, 100.0f);
		Scale = 0.0f;
		Curve = 0.0f;
		Open = 0.0f;
	}
	Size = D3DXVECTOR2(sizeX, sizeY);
	Position = D3DXVECTOR2(posX, posY);
	this->C2DUIPolygon::Init(sizeX, sizeY, posX, posY, texture);
}
void C2DUIMenuLogo::Init(float sizeX, float sizeY, float posX, float posY)
{
	{
		Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Position = D3DXVECTOR2(0.0f, 0.0f);
		Size = D3DXVECTOR2(100.0f, 100.0f);
		Scale = 0.0f;
		Curve = 0.0f;
		Open = 0.0f;
	}
	Size = D3DXVECTOR2(sizeX, sizeY);
	Position = D3DXVECTOR2(posX, posY);
	this->C2DUIPolygon::Init(sizeX, sizeY, posX, posY);
}
void C2DUIMenuLogo::Init(float sizeX, float sizeY)
{
	{
		Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Position = D3DXVECTOR2(0.0f, 0.0f);
		Size = D3DXVECTOR2(100.0f, 100.0f);
		Scale = 0.0f;
		Curve = 0.0f;
		Open = 0.0f;
	}
	Size = D3DXVECTOR2(sizeX, sizeY);
	this->C2DUIPolygon::Init(sizeX, sizeY, 0.0f, 0.0f);
}

//----�Œ�--------
void C2DUIMenuLogo::ReSet(void)
{
	SetVertex(Size.x, Size.y, Position.x, Position.y);
	SetVertex(Color);
}

//----�A�j���[�V����01--------
void C2DUIMenuLogo::Animation01(void)
{
	float scale = cosf(Scale += 0.05f) / 10.0f + 1.0f;
	SetVertex(Size.x * scale, Size.y * scale);
	SetPosition(Position.x, Position.y);
}

//----�A�j���[�V����02--------
void C2DUIMenuLogo::Animation02(void)
{
	SetVertex(D3DXCOLOR(0.2f, 1.0f, 0.4f, 1.0f));
}

//----Open01--------
void C2DUIMenuLogo::Open01(void)
{
	if (Open < 1.0f)
	{
		Open += 0.05f;
		D3DXVECTOR2 size = Size * Open;
		SetVertex(size.x, size.y, Position.x, Position.y);
	}
}


/* �p�[�Z���g�Q�[�W */
//----������--------
void C2DUIPercentGauge::Init(const char *textureF, const char *textureG)
{
	Frame.Init(textureF);
	Gage.Init(textureG);
}
void C2DUIPercentGauge::Init(float sizeX, float sizeY, float posX, float posY)
{
	Size.x = sizeX;
	Size.y = sizeY;
	Position.x = posX;
	Position.y = posY;

	float cor = sizeX * 0.04f;

	Frame.Init(sizeX, sizeY, posX, posY);
	Gage.Init(sizeX - cor, sizeY - cor, posX, posY);
}

//----�I��--------
void C2DUIPercentGauge::Uninit(void)
{
	Frame.ReleaseBuffer();
	Gage.ReleaseBuffer();
}

//----�X�V--------
void C2DUIPercentGauge::Update(float per)
{
	float cor = Size.x * 0.04f;

	Gage.Vertex[1].vtx = D3DXVECTOR3(-(Size.x - cor) + Position.x, -(Size.y - cor) + Position.y, 0.0f);
	Gage.Vertex[3].vtx = D3DXVECTOR3(-(Size.x - cor) + Position.x,  (Size.y - cor) + Position.y, 0.0f);

	Gage.Vertex[1].vtx.x += ((Size.x - cor) * 2.0f) * per;
	Gage.Vertex[3].vtx.x += ((Size.x - cor) * 2.0f) * per;

}

//----�`��--------
void C2DUIPercentGauge::Draw(void)
{
	Frame.Draw();
	Gage.Draw();
}



