//=============================================================================
//
// カメラ処理 [Camera.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_SIZE		(10.0f)	// カメラの当たり判定時に使用(正六面体)

#define	VIEW_ANGLE		(D3DXToRadian(45))								// ビュー平面の視野角(45度)
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(32768.0f)										// ビュー平面のFarZ値

// デバッグ
#define _DEBUG_MODE_CAMERA_ (1)

#if _DEBUG_MODE_CAMERA_

#define	CAMERA_MOVE_VALUE	(2.0f)		// 移動量
#define	GAZE_MOVE_VALUE		(0.005f)	// 移動量

#endif // _DEBUG_MODE_CAMERA_


enum CAMERA_STATUS
{
	CAMERA_POSITION,	// カメラの位置
	CAMERA_FOCUS,		// 注視点
	CAMERA_GAZE,		// 視線ベクトル
	CAMERA_ROTATION,	// カメラの回転
	CAMERA_UPSIDE,		// 上方向ベクトル
};

//*****************************************************************************
// 構造体
//*****************************************************************************


//*****************************************************************************
// クラス設計
//*****************************************************************************
class CCamera
{
public:
	D3DXVECTOR3		Position;			// カメラの座標
	D3DXVECTOR3		Gaze;				// カメラの視線先
	D3DXVECTOR3		UpVector;			// カメラの上方向ベクトル
	D3DXVECTOR3		Angle;				// カメラのアングル

	float			Interval;			// カメラの視点と視線先の距離
	float			Sensitivity;		// マウス感度

	D3DXMATRIX		ViewMatrix;			// ビューマトリックス
	D3DXMATRIX		ProjectionMatrix;	// プロジェクションマトリックス

public:
	CCamera();
	~CCamera();

	void Init(void);

	void CreateMatrix(void);

	void Translation(D3DXVECTOR2 moveRate);
	void Rotation(D3DXVECTOR2 moveRate);
	void Scaling(float moveRate);
	void FollowingFocus(D3DXVECTOR3 correction);
	void Tracking(D3DXVECTOR3 target);
	void UNIQ_DebugMove(void);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetFocus(void);
	D3DXVECTOR3 GetGazeVector(void);
	D3DXVECTOR3 GetAngle(void);
	D3DXVECTOR3 GetUpVector(void);
	float       GetIntervel(void);
	D3DXMATRIX  GetViewMatrix(void);
	D3DXMATRIX  GetProjectionMatrix(void);

	void SetPosition(D3DXVECTOR3 vector);
	void SetFocus(D3DXVECTOR3 vector);
	void SetAngle(D3DXVECTOR3 vector);
	void SetUpVector(D3DXVECTOR3 vector);
	void SetIntervel(float distance);

private:

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(D3DXVECTOR3 target);
void SetCamera(void);

D3DXMATRIX GetMtxView(void);

#endif
