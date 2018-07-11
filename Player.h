//=============================================================================
//
// プレイヤー処理 [Player.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _OBJECT_PLAYER_INCLUDE_H_
#define _OBJECT_PLAYER_INCLUDE_H_


#include "Library\ObjectBase3D.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_PLAYER_ZPOS (-60.0f)

#define TEXTURE_PLAYER		_T("data/TEXTURE/PLAYER/Player.png")	// プレイヤー画像
#define TEXTURE_PLAYER2		_T("data/TEXTURE/PLAYER/PlayerAnime.png")	// プレイヤー画像
#define TEXTURE_FRIEND		_T("data/TEXTURE/PLAYER/Friend.png")	// プレイヤー画像
#define TEXTURE_FRIEND2		_T("data/TEXTURE/PLAYER/FriendAnime.png")	// プレイヤー画像

#define DATAFILE_PLAYER_ROUTE	"data/STAGE/RouteData.txt"

#define PLAYER_MOVE_SPEED	(10.0f)	// プレイヤーの移動速度

#define PLAYER_MAX		(1)		//プレイヤー最大数

//*****************************************************************************
// クラス設計
//*****************************************************************************

class PlayerB : public C3DPolygonObject
{
	float Speed;	// 移動速度

public:
	PlayerB() {};
	~PlayerB() {};

	void LoadPlayerStatus(float posX, int bx, int by, float x, float y);
	void Animation(void);
	void Move(D3DXVECTOR3 vec);
	void SetZeroTexture(void);

	void Init(const char *texture);
	void Init(const char *texture, int x, int y);
	int Update(void);
	void Uninit(void);

	void SetPositionX(float posX)
	{
		Position.x = posX;
	}
	D3DXVECTOR3 GetPosition(void)
	{
		return Position;
	}

private:
	void SetTexture(void);

};

class PlayerC : public C3DPolygonObject
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
