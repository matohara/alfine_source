//=============================================================================
//
// �v���C���[���� <Player.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "Player.h"
#include "Library\Input.h"


//----�v���C���[���Z�b�g--------
void PlayerB::LoadPlayerStatus(float posX, int bx, int by, float x, float y)
{
	this->LoadTextureStatus(x, y, 1.0f, bx, by, 10);
	this->Position = D3DXVECTOR3(posX, y, GAME_PLAYER_ZPOS);
	this->Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Speed = PLAYER_MOVE_SPEED;
	this->MakeVertex();
}

//----�A�j���[�V����--------
void PlayerB::Animation(void)
{
	if ((TexPattern_X * TexPattern_Y) > 1)// �e�N�X�`����ނ����̏ꍇ�̓X�L�b�v
	{
		/* �A�j���[�V���� */
		AnimeCount++;
		if ((AnimeCount % ChangeAnimeTime) == 0)
		{
			// �p�^�[���̐؂�ւ�
			AnimePattern = (AnimePattern + 1) % (TexPattern_X * TexPattern_Y);
			// �e�N�X�`�����W��ݒ�
			SetTexture();
		}
	}
}

//----�ړ�--------
void PlayerB::Move(D3DXVECTOR3 vec)
{
	Position += vec;
}

//----0�e�N�X�`��--------
void PlayerB::SetZeroTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----����������--------
void PlayerB::Init(const char *texture)
{
	// ��񃊃Z�b�g
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
		this->Speed = 0.0f;	// �ړ����x
	}
	this->LoadTexture(texture);							// �e�N�X�`���ǂݍ���
	this->LoadPlayerStatus(-512, 1, 1, 19.0f, 30.5f);	// �v���C���[�����Z�b�g
	this->SetTexture();									// �����e�N�X�`���ɐݒ�
}
void PlayerB::Init(const char *texture, int x, int y)
{
	// ��񃊃Z�b�g
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
		this->Speed = 0.0f;	// �ړ����x(��������)
	}
	this->LoadTexture(texture);							// �e�N�X�`���ǂݍ���
	this->LoadPlayerStatus(-512, x, y, 21.4f, 32.4f);	// �v���C���[�����Z�b�g
	this->SetTexture();									// �����e�N�X�`���ɐݒ�
}

//----�X�V����--------
int PlayerB::Update(void)
{
	Animation();

	Position.x += Speed;

	if (Position.x > 16500)
	{
		return 1;
	}

	PrintDebugProcess("�v���C���[�ʒu : �i%f, %f, %f�j\n", Position.x, Position.y, Position.z);
	return 0;
}

//----�I������--------
void PlayerB::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	Release();
}

//--�e�N�X�`�����W�̐ݒ�--//
void PlayerB::SetTexture(void)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = AnimePattern % TexPattern_X;
	int y = AnimePattern / TexPattern_X;
	float sizeX = 1.0f / TexPattern_X;
	float sizeY = 1.0f / TexPattern_Y;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}


//----�v���C���[���Z�b�g--------
void PlayerC::LoadPlayerStatus(int bx, int by, float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, bx, by, 10);

	Position = D3DXVECTOR3(0.0f, y, GAME_PLAYER_ZPOS);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----�A�j���[�V����--------
void PlayerC::Animation(void)
{
	if ((TexPattern_X * TexPattern_Y) > 1)// �e�N�X�`����ނ����̏ꍇ�̓X�L�b�v
	{
		/* �A�j���[�V���� */
		AnimeCount++;
		if ((AnimeCount % ChangeAnimeTime) == 0)
		{
			// �p�^�[���̐؂�ւ�
			AnimePattern = (AnimePattern + 1) % (TexPattern_X * TexPattern_Y);
			// �e�N�X�`�����W��ݒ�
			SetTexture();
		}
	}
}

//----�ړ�--------
void PlayerC::GoPoint(float x)
{
	Position.x += x;
}
void PlayerC::SetPosition(D3DXVECTOR3 pos)
{
	Position = pos;
}
void PlayerC::SetPosition(float x)
{
	Position.x = x;
}

//----0�e�N�X�`��--------
void PlayerC::ReSetTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----����������--------
void PlayerC::Init(const char *texture)
{
	// ��񃊃Z�b�g
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

	// �e�N�X�`���ǂݍ���
	LoadTexture(texture);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(1, 1, 30.0f, 30.0f);

	// �����e�N�X�`���ɐݒ�
	SetTexture();
}
void PlayerC::Init(const char *texture, int x, int y)
{
	// ��񃊃Z�b�g
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

	// �e�N�X�`���ǂݍ���
	LoadTexture(texture);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(x, y, 21.0f, 30.0f);

	// �����e�N�X�`���ɐݒ�
	SetTexture();
}

//----�X�V����--------
void PlayerC::Update(float x)
{
	Animation();

	Position.x = x;
}

//----�I������--------
void PlayerC::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	Release();
}

//--�e�N�X�`�����W�̐ݒ�--//
void PlayerC::SetTexture(void)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = AnimePattern % TexPattern_X;
	int y = AnimePattern / TexPattern_X;
	float sizeX = 1.0f / TexPattern_X;
	float sizeY = 1.0f / TexPattern_Y;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}


