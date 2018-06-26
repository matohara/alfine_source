//=============================================================================
//
// �J�������� [Camera.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _CAMERA_INCLUDE_H_
#define _CAMERA_INCLUDE_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SIZE		(10.0f)	// �J�����̓����蔻�莞�Ɏg�p(���Z�ʑ�)

#define	VIEW_ANGLE		(D3DXToRadian(45))								// �r���[���ʂ̎���p(45�x)
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(32768.0f)										// �r���[���ʂ�FarZ�l

// �f�o�b�O
#define _DEBUG_MODE_CAMERA_ (1)

#if _DEBUG_MODE_CAMERA_

#define	CAMERA_MOVE_VALUE	(2.0f)		// �ړ���
#define	GAZE_MOVE_VALUE		(0.005f)	// �ړ���

#endif // _DEBUG_MODE_CAMERA_


enum CAMERA_STATUS
{
	CAMERA_POSITION,	// �J�����̈ʒu
	CAMERA_FOCUS,		// �����_
	CAMERA_GAZE,		// �����x�N�g��
	CAMERA_ROTATION,	// �J�����̉�]
	CAMERA_UPSIDE,		// ������x�N�g��
};

//*****************************************************************************
// �\����
//*****************************************************************************


//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class CCamera
{
public:
	D3DXVECTOR3		Position;			// �J�����̍��W
	D3DXVECTOR3		Gaze;				// �J�����̎�����
	D3DXVECTOR3		UpVector;			// �J�����̏�����x�N�g��
	D3DXVECTOR3		Angle;				// �J�����̃A���O��

	float			Interval;			// �J�����̎��_�Ǝ�����̋���
	float			Sensitivity;		// �}�E�X���x

	D3DXMATRIX		ViewMatrix;			// �r���[�}�g���b�N�X
	D3DXMATRIX		ProjectionMatrix;	// �v���W�F�N�V�����}�g���b�N�X

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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(D3DXVECTOR3 target);
void SetCamera(void);

D3DXMATRIX GetMtxView(void);

#endif
