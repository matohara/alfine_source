//=============================================================================
//
// �v���C���[���� [Player.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _OBJECT_PLAYER_INCLUDE_H_
#define _OBJECT_PLAYER_INCLUDE_H_


#include "../class/Aclass_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_PLAYER_ZPOS (-60.0f)

#define TEXTURE_PLAYER		_T("data/TEXTURE/PLAYER/Player.png")	// �v���C���[�摜
#define TEXTURE_PLAYER2		_T("data/TEXTURE/PLAYER/PlayerAnime.png")	// �v���C���[�摜
#define TEXTURE_FRIEND		_T("data/TEXTURE/PLAYER/Friend.png")	// �v���C���[�摜
#define TEXTURE_FRIEND2		_T("data/TEXTURE/PLAYER/FriendAnime.png")	// �v���C���[�摜

#define DATAFILE_PLAYER_ROUTE	"data/STAGE/RouteData.txt"

#define PLAYER_MOVE_SPEED	(10.0f)	// �v���C���[�̈ړ����x

#define PLAYER_MAX		(1)		//�v���C���[�ő吔

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class PlayerRoute
{
public:
	D3DXVECTOR3 Point;	// ���Ɍ������ׂ��ʒu
	int Time;			// �����܂łɂ�����t���[����

	PlayerRoute()
	{
		Point = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Time = 60;
	};
	PlayerRoute(D3DXVECTOR3 point, int time)
	{
		Point = point;
		Time = time;
	}
	~PlayerRoute() {};

private:

};

class PlayerA : public class_ObjectA
{
	PlayerRoute **Route;	// �ړ����[�g�ۑ��p�|�C���^�[
	int MapNumber;			// �}�b�v�ԍ�
	int NextPoint;			// ���̈ړ���ԍ�
	int RouteCounter;		// �ړ��i�s�x
	int *PointMax;			// �ړ��|�C���g��
	int MapMax;				// �}�b�v�ő吔
public:

	PlayerA() {};
	~PlayerA() {};

	void LoadPlayerStatus(float x, float y);
	void LoadRoute();

	void Init(void);
	int Update(void);
	void Draw(void);
	void Uninit(void);

	void ReleaseRouteData(void);

	int GetMapNumber(void)
	{
		return MapNumber;
	};
	D3DXVECTOR3 GetPosition(void)
	{
		return Position;
	}
	D3DXVECTOR3 GetPosition(float x, float y, float z)
	{
		return (Position + D3DXVECTOR3(x, y, z));
	}

private:
	void SetTexture(void);

};

class PlayerB : public class_ObjectA
{
	float Speed;		// �ړ����x(��������)
	int MapNumber;		// �}�b�v�ԍ�
	int RouteCounter;	// �ړ��i�s�x
	int MapMax;			// �}�b�v�ő吔

public:
	PlayerB() {};
	~PlayerB() {};

	void LoadPlayerStatus(int bx, int by, float x, float y);
	void Animation(void);
	void GoPoint(D3DXVECTOR3 vec);
	void ReSetTexture(void);

	void Init(const char *texture);
	void Init(const char *texture, int x, int y);
	int Update(void);
	void Draw(void);
	void Uninit(void);

	int GetMapNumber(void)
	{
		return MapNumber;
	};
	D3DXVECTOR3 GetPosition(void)
	{
		return Position;
	}
	D3DXVECTOR3 GetPosition(float x, float y, float z)
	{
		return (Position + D3DXVECTOR3(x, y, z));
	}

private:
	void SetTexture(void);

};

class PlayerC : public class_ObjectA
{
public:
	PlayerC() {};
	~PlayerC() {};

	void LoadPlayerStatus(int bx, int by, float x, float y);
	void Animation(void);
	void GoPoint(float x);
	void ReSetTexture(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetPosition(float x);

	void Init(const char *texture);
	void Init(const char *texture, int x, int y);
	void Update(float x);
	void Draw(void);
	void Uninit(void);

	D3DXVECTOR3 GetPosition(void)
	{
		return Position;
	}
	D3DXVECTOR3 GetPosition(float x, float y, float z)
	{
		return (Position + D3DXVECTOR3(x, y, z));
	}

	void FlipX(void);

private:
	void SetTexture(void);

};



#endif
