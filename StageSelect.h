//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.h]
// Author : ���ˌ��j��
//
//=============================================================================
#ifndef _STAGESELECT_INCLUDE_H_
#define _STAGESELECT_INCLUDE_H_

#include "Library\ObjectBase2D.h"
#include "main.h"

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************

/*�o�����N���X */
class Barrel : public C2DObject
{
public:
	Barrel() {};			// �R���X�g���N�^
	~Barrel() {};			// �f�X�g���N�^

	// �|�W�V�����ړ��֐�
	void LogoMove(float posX, float posY)
	{
		Position.x += posX;		// x��
		Position.y += posY;		// y��
	}

	// ���S�T�C�Y�X�V�֐�
	void LogoSize(float sizeX, float sizeY)
	{

		float risc = 1.41421356f;
		Vertex[0].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) + Angle) * risc * sizeX * Scale;
		Vertex[0].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) + Angle) * risc * sizeY * Scale;
		Vertex[0].vtx.z = 0.0f;
		Vertex[1].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) - Angle) * risc * sizeX * Scale;
		Vertex[1].vtx.y = Position.y - sinf((D3DX_PI * 0.25f) - Angle) * risc * sizeY * Scale;
		Vertex[1].vtx.z = 0.0f;
		Vertex[2].vtx.x = Position.x - cosf((D3DX_PI * 0.25f) - Angle) * risc * sizeX * Scale;
		Vertex[2].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) - Angle) * risc * sizeY * Scale;
		Vertex[2].vtx.z = 0.0f;
		Vertex[3].vtx.x = Position.x + cosf((D3DX_PI * 0.25f) + Angle) * risc * sizeX * Scale;
		Vertex[3].vtx.y = Position.y + sinf((D3DX_PI * 0.25f) + Angle) * risc * sizeY * Scale;
		Vertex[3].vtx.z = 0.0f;

	}

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

#endif
