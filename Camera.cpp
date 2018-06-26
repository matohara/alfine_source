//=============================================================================
//
// �J�������� [Camera.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Camera.h"
#include "input.h"
#include "DebugProcess.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	CAMERA_GAZE_X		(0.0f)		// �J����1(Main)���_�̏����ʒu(X���W)
//#define	CAMERA_GAZE_Y		( 120.0f)	// �J����1(Main)���_�̏����ʒu(Y���W)
//#define	CAMERA_GAZE_Z		(-400.0f)	// �J����1(Main)���_�̏����ʒu(Z���W)

#define GAMECAMERA_XLIMIT_MIN (-1000)
#define GAMECAMERA_XLIMIT_MAX ( 1000)

#define CtoA_INTERVAL_MAX	(640.0f)	// �J�����ƒ����_�Ԃ̍ő勗��
#define CtoA_INTERVAL_MIN	(240.0f)	// �J�����ƒ����_�Ԃ̍ŏ�����
#define CAMERA_ANGLE		(10)

int g_iAngle = CAMERA_ANGLE;

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
//----�R���X�g���N�^--------
CCamera::CCamera()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);
	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----�f�X�g���N�^--------
CCamera::~CCamera()
{

}

//----������--------
void CCamera::Init(void)
{
	// �J�����̏�����
	Gaze = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;

	UpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	Angle = D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f);

	Interval = CtoA_INTERVAL_MIN;
	Sensitivity = GAZE_MOVE_VALUE;
}

//----���s�ړ�--------
void CCamera::Translation(D3DXVECTOR2 moveRate)
{
	/* �\���x�N�g�� */
	D3DXVECTOR3 LeftVec, FrontVec;
	D3DXVECTOR3 gazeVec = Gaze - Position;
	D3DXVECTOR3 subVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVec3Cross(&LeftVec, &gazeVec, &subVec);
	D3DXVec3Normalize(&LeftVec, &LeftVec);
	D3DXVec3Cross(&FrontVec, &LeftVec, &gazeVec);
	D3DXVec3Normalize(&FrontVec, &FrontVec);
	D3DXVec3Normalize(&gazeVec, &gazeVec);

	/* ���_���s�ړ� */
	if (IsMouseCenterPressed())
	{
		Gaze += LeftVec *  moveRate.x * CAMERA_MOVE_VALUE;
		Gaze += FrontVec * moveRate.y * CAMERA_MOVE_VALUE;
	}
}

//----�O��ړ�--------
void CCamera::Scaling(float moveRate)
{
	D3DXVECTOR3 gazeVec = Gaze - Position;

	/* �g��E�k�� */
	//gazeVec *= moveRate * 0.001f;
	//Gaze += gazeVec;

	Interval -= moveRate;
}

//----����ړ�--------
void CCamera::Rotation(D3DXVECTOR2 moveRate)
{
	/* �J�����ʒu */
	// �ړ�����
	if (IsMouseLeftPressed())
	{
		Angle.x -= moveRate.y * Sensitivity;
		Angle.z -= moveRate.x * Sensitivity;
		Angle.y += moveRate.x * Sensitivity;
	}

	/* �ړ��͈͐��� */
	if (Angle.x > D3DXToRadian(179))
	{
		Angle.x = D3DXToRadian(179);
	}
	if (Angle.x < D3DXToRadian(1))
	{
		Angle.x = D3DXToRadian(1);
	}
	if (Angle.z > D3DX_PI)
	{
		Angle.z -= D3DX_PI * 2.0f;
		Angle.y += D3DX_PI * 2.0f;
	}
	if (Angle.z < -D3DX_PI)
	{
		Angle.z += D3DX_PI * 2.0f;
		Angle.y -= D3DX_PI * 2.0f;
	}

	/* ���̍��W�ֈړ� */
	float sinTheta = sinf(Angle.x);
	Position.x = Interval * sinTheta * cosf(Angle.z);
	Position.y = Interval * cosf(Angle.x);
	Position.z = Interval * sinTheta * sinf(Angle.z);
	// ���̍��W�̔��f
	Position += Gaze;
}

//----�ǔ�--------
void CCamera::Tracking(D3DXVECTOR3 target)
{
	Gaze = target + D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	if (Gaze.x < GAMECAMERA_XLIMIT_MIN)
	{
		Gaze.x = GAMECAMERA_XLIMIT_MIN;
	}
	if (Gaze.x > GAMECAMERA_XLIMIT_MAX)
	{
		Gaze.x = GAMECAMERA_XLIMIT_MAX;
	}
	Position.x = 0.0f;
	Position.y = Interval * sinf(D3DXToRadian(CAMERA_ANGLE));
	Position.z = Interval * -cosf(D3DXToRadian(CAMERA_ANGLE));
	Position += Gaze;
}

//----�f�o�b�O�O��--------
void CCamera::UNIQ_DebugMove(void)
{
	float move = 2.0f;

	// �z�[���h�E�I��
	if (GetKeyboardPress(DIK_W))
	{
		Position.z += move;
		Gaze.z += move;
	}
	if (GetKeyboardPress(DIK_S))
	{
		Position.z -= move;
		Gaze.z -= move;
	}
	if (GetKeyboardPress(DIK_E))
	{
		Position.y += move;
		Gaze.y += move;
	}
	if (GetKeyboardPress(DIK_D))
	{
		Position.y -= move;
		Gaze.y -= move;
	}
	if (GetKeyboardTrigger(DIK_Q))
	{
		g_iAngle++;
		Position.y = 100.0f * sinf(D3DXToRadian(g_iAngle));
		Position.z = 100.0f * -cosf(D3DXToRadian(g_iAngle));
		Position += Gaze;
	}
	if (GetKeyboardTrigger(DIK_A))
	{
		g_iAngle--;
		Position.y = 100.0f * sinf(D3DXToRadian(g_iAngle));
		Position.z = 100.0f * -cosf(D3DXToRadian(g_iAngle));
		Position += Gaze;
	}

	PrintDebugProcess("�J�����ʒu : (%f, %f, %f)\n", Position.x, Position.y, Position.z);
	PrintDebugProcess("�J�������� : (%f, %f, %f)\n", Gaze.x, Gaze.y, Gaze.z);
	PrintDebugProcess("�J�����p�x : (%d)\n", g_iAngle);
}

//----������Ǐ]--------
void CCamera::FollowingFocus(D3DXVECTOR3 correction)
{
	Position = Gaze + correction;
}

//----�}�g���b�N�X����--------
void CCamera::CreateMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* �r���[�}�g���b�N�X */
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ViewMatrix);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&ViewMatrix,
		&Position,		// �J�����̎��_
		&Gaze,			// ������
		&UpVector);		// �����

						// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);


	/* �v���W�F�N�V�����}�g���b�N�X */
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ProjectionMatrix);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix,
		VIEW_ANGLE,		// �r���[���ʂ̎���p
		VIEW_ASPECT,	// �r���[���ʂ̃A�X�y�N�g��
		VIEW_NEAR_Z,	// �r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	// �r���[���ʂ�FarZ�l

						// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

/*----�擾�֐�----*/
D3DXVECTOR3 CCamera::GetPosition(void)			{ return Position; }			//--�J�����̍��W
D3DXVECTOR3 CCamera::GetFocus(void)				{ return Gaze; }				//--�J�����̒����_
D3DXVECTOR3 CCamera::GetGazeVector(void)		{ return (Gaze - Position); }	//--�J�����̎���
D3DXVECTOR3 CCamera::GetAngle(void)				{ return Angle; }				//--�J�����̃A���O��
D3DXVECTOR3 CCamera::GetUpVector(void)			{ return UpVector; }			//--�J�����̏����
D3DXMATRIX  CCamera::GetViewMatrix(void)		{ return ViewMatrix; }			//--�r���[�}�g���b�N�X
D3DXMATRIX  CCamera::GetProjectionMatrix(void)	{ return ProjectionMatrix; }	//--�v���W�F�N�V�����}�g���b�N�X
float       CCamera::GetIntervel(void)			{ return Interval; }			//--����

/*----�㏑�֐�----*/
void CCamera::SetPosition(D3DXVECTOR3 vector)	{ Position = vector; }	//--�J�����̍��W
void CCamera::SetFocus(D3DXVECTOR3 vector)		{ Gaze = vector; }		//--�J�����̒����_
void CCamera::SetAngle(D3DXVECTOR3 vector)		{ Angle = vector; }		//--�J�����̃A���O��
void CCamera::SetUpVector(D3DXVECTOR3 vector)	{ UpVector = vector; }	//--�J�����̏����
void CCamera::SetIntervel(float distance)		{ Interval = distance; }//--����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CCamera GameCamera;

#if _DEBUG_MODE_CAMERA_
CCamera DebugCamera;
bool DebugCameraFlag = false;
#endif // _DEBUG_MODE_CAMERA_


//=============================================================================
// ����������
//=============================================================================
HRESULT InitCamera(void)
{
	// �Q�[���J����
	GameCamera.Init();

#if _DEBUG_MODE_CAMERA_
	// �f�o�b�N�J����
	DebugCamera.Init();
#endif // _DEBUG_MODE_CAMERA_


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCamera(D3DXVECTOR3 target)
{
	// �Q�[���J����
	GameCamera.UNIQ_DebugMove();
	GameCamera.Scaling(GetMouseZ() / 10.0f);
	GameCamera.Tracking(target);

	PrintDebugProcess("�Q�[���J�������� : (%f)\n", GameCamera.Interval);

#if _DEBUG_MODE_CAMERA_
	// �؂�ւ�
	if (GetKeyboardTrigger(DIK_C))
	{
		DebugCameraFlag = DebugCameraFlag ? false : true;
	}

	if (DebugCameraFlag)
	{
		// �f�o�b�N�J����
		D3DXVECTOR3 MouseMovement = D3DXVECTOR3((float)GetMouseX(), (float)GetMouseY(), (float)GetMouseZ());
		DebugCamera.Translation(D3DXVECTOR2(MouseMovement.x, MouseMovement.y));
		DebugCamera.Scaling(MouseMovement.z);
		DebugCamera.Rotation(D3DXVECTOR2(MouseMovement.x, MouseMovement.y));
	}
#endif // _DEBUG_MODE_CAMERA_

}

//=============================================================================
// �`�揈��
//=============================================================================
void SetCamera(void)
{
#if _DEBUG_MODE_CAMERA_
	if (DebugCameraFlag)
	{
		// �f�o�b�N�J����
		DebugCamera.CreateMatrix();
	}
	else
	{
		// �Q�[���J����
		GameCamera.CreateMatrix();
	}
#else
	// �Q�[���J����
	GameCamera.CreateMatrix();
#endif // _DEBUG_MODE_CAMERA_

}

//=============================================================================
// �r���[�}�g���b�N�X�擾�֐�
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return GameCamera.GetViewMatrix();
}

