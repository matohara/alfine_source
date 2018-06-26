//=============================================================================
//
// �v���C���[���� [Player.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "../../main.h"
#include "../../input.h"

#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

//----�v���C���[���Z�b�g--------
void PlayerA::LoadPlayerStatus(float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, 7, 1, 10);

	Position = D3DXVECTOR3(0.0f, y, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	MakeVertex();
}

//----���[�g�ǂݍ���--------
void PlayerA::LoadRoute(void)
{
	// Output �󂯎��
	FILE *fp = fopen(DATAFILE_PLAYER_ROUTE, "r");	// �t�@�C�����J��

	// �t�@�C�����J�������`�F�b�N
	if (fp == NULL)
	{
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

	fscanf(fp, "%d", &MapMax);
	PointMax = new int[MapMax];

	// �t�@�C������ǂݍ���
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		fscanf(fp, "%d", &PointMax[iCnt]);
	}

	// ���[�g�f�[�^�����
	{
		char comment[256];
		fscanf(fp, "%s", comment);
		if (strcmp(comment, "#ROUTE_DATA"))
		{
			MessageBox(GethWnd(), "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "ERROR=\"File Read2\"", MB_YESNO);
		}
	}

	// �������m��
	Route = new PlayerRoute*[MapMax];
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		Route[iCnt] = new PlayerRoute[PointMax[iCnt]];
	}

	char skep;
	for (int iCnt = 0; iCnt < MapMax; iCnt++)
	{
		for (int iCnt2 = 0; iCnt2 < PointMax[iCnt]; iCnt2++)
		{
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.x);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.y);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%f", &Route[iCnt][iCnt2].Point.z);
			fscanf(fp, "%c", &skep);
			fscanf(fp, "%d", &Route[iCnt][iCnt2].Time);
			fscanf(fp, "%c", &skep);
		}
	}

	fclose(fp);	// �t�@�C������I��

}


//----����������--------
void PlayerA::Init(void)
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

		Route = NULL;		// �ړ����[�g�ۑ��p�|�C���^�[
		MapNumber = 0;		// ���̃}�b�v�ԍ�
		NextPoint = 0;		// ���̈ړ���ԍ�
		RouteCounter = 0;	// �ړ��i�s�x
		PointMax = NULL;	// �ړ��|�C���g��
		MapMax = 0;			// �}�b�v�ő吔
	}

	// �e�N�X�`���ǂݍ���
	LoadTexture(TEXTURE_PLAYER2);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(21.4f, 32.4f);

	// �����e�N�X�`���ɐݒ�
	SetTexture();

	// �ړ����[�g��ݒ�
	LoadRoute();
}

//----�X�V����--------
int PlayerA::Update(void)
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

	if (NextPoint == 0)
	{// ���_�͏u���ړ�
		Position = Route[MapNumber][NextPoint].Point;
		NextPoint++;
	}
	else
	{// �w��|�C���g�܂ňړ�
		// �ړ��x�N�g�������߂�
		Position += (Route[MapNumber][NextPoint].Point - Route[MapNumber][NextPoint - 1].Point) / (float)Route[MapNumber][NextPoint].Time;
		RouteCounter++;
		if (RouteCounter == Route[MapNumber][NextPoint].Time)
		{// �w��t���[�����ړ��I��
			RouteCounter = 0;
			NextPoint++;
		}

		// �S�|�C���g���ړ��㎟�̃}�b�v��
		if (NextPoint >= PointMax[MapNumber])
		{
			MapNumber++;
			NextPoint = 0;
		}

		// *�S�}�b�v�I����I��
		if (MapNumber >= MapMax)
		{
			MapNumber = MapMax - 1;
			return 1;
		}
	}

	return 0;
}

//----�`�揈��--------
void PlayerA::Draw(void)
{
	// �`��
	this->class_ObjectA::DrawBillboard();
}

//----�I������--------
void PlayerA::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	ReleaseBuffer();

	// ���[�g�f�[�^�������J��
	ReleaseRouteData();
}

//----�������J��--------
void PlayerA::ReleaseRouteData(void)
{
	for (int i = 0; i < MapMax; i++)
	{
		delete[] Route[i];
	}
	delete[] Route;
	Route = NULL;

	delete[] PointMax;
	PointMax = NULL;
}

//--�e�N�X�`�����W�̐ݒ�--//
void PlayerA::SetTexture(void)
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
void PlayerB::LoadPlayerStatus(int bx, int by, float x, float y)
{
	LoadTextureStatus(x, y, 1.0f, bx, by, 10);

	Position = D3DXVECTOR3(-1200.0f, y, GAME_PLAYER_ZPOS);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Speed = 2;

	MakeVertex();
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
void PlayerB::GoPoint(D3DXVECTOR3 vec)
{
	Position += vec;
}

//----0�e�N�X�`��--------
void PlayerB::ReSetTexture(void)
{
	AnimePattern = 0;
	SetTexture();
}

//----����������--------
void PlayerB::Init(const char *texture)
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

		Speed = 0.0f;		// �ړ����x(��������)
		MapNumber = 0;		// ���̃}�b�v�ԍ�
		RouteCounter = 0;	// �ړ��i�s�x
		MapMax = 4;			// �}�b�v�ő吔
	}

	// �e�N�X�`���ǂݍ���
	LoadTexture(texture);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(1, 1, 19.0f, 30.5f);

	// �����e�N�X�`���ɐݒ�
	SetTexture();
}
void PlayerB::Init(const char *texture, int x, int y)
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

		Speed = 0.0f;		// �ړ����x(��������)
		MapNumber = 0;		// ���̃}�b�v�ԍ�
		RouteCounter = 0;	// �ړ��i�s�x
		MapMax = 4;			// �}�b�v�ő吔
	}

	// �e�N�X�`���ǂݍ���
	LoadTexture(texture);

	// �v���C���[�����Z�b�g
	LoadPlayerStatus(x, y, 21.4f, 32.4f);

	// �����e�N�X�`���ɐݒ�
	SetTexture();
}

//----�X�V����--------
int PlayerB::Update(void)
{
	Animation();

	Position.x += Speed;

	if (Position.x > 1100.0f)
	{
		MapNumber++;
		Position.x = -1100.0f;
	}

	// *�S�}�b�v�I����I��
	if (MapNumber >= MapMax)
	{
		MapNumber = MapMax - 1;
		return 1;
	}

	PrintDebugProcess("�v���C���[�ʒu : �i%f, %f, %f�j\n", Position.x, Position.y, Position.z);
	return 0;
}

//----�`�揈��--------
void PlayerB::Draw(void)
{
	// �`��
	this->class_ObjectA::DrawBillboard();
}

//----�I������--------
void PlayerB::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	ReleaseBuffer();
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

//----�`�揈��--------
void PlayerC::Draw(void)
{
	// �`��
	this->class_ObjectA::DrawBillboard();
}

//----�I������--------
void PlayerC::Uninit(void)
{
	// �e�N�X�`���o�b�t�@�J��
	ReleaseBuffer();
}

//----�e�N�X�`�����]--------
void PlayerC::FlipX(void)
{
	D3DXVECTOR2 tex;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		tex = pVtx[0].tex;
		pVtx[0].tex = pVtx[1].tex;
		pVtx[1].tex = tex;
		tex = pVtx[2].tex;
		pVtx[2].tex = pVtx[3].tex;
		pVtx[3].tex = tex;

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
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


