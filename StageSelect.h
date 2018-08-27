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
// �}�N����`
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/���j���[��ʔw�i.png"
#define STAGESELECT_TEX_UI		     "data/TEXTURE/UI/OptionBar.png"

#define BG_STAGE_ONE				"data/TEXTURE/STAGEVIEW/�C���[�W�P.png"		// �e�N�X�`���F�X�e�[�W�P
#define BG_STAGE_TWO				"data/TEXTURE/STAGEVIEW/�C���[�W�Q.png"		// �e�N�X�`���F�X�e�[�W�Q
#define BG_STAGE_THREE				"data/TEXTURE/STAGEVIEW/�C���[�W�R.png"		// �e�N�X�`���F�X�e�[�W�R
#define BG_STAGE_FOUR				"data/TEXTURE/STAGEVIEW/�C���[�W�S.png"		// �e�N�X�`���F�X�e�[�W�S
#define BG_STAGE_POS_X				(300)										// BG�z�ux��(y���̓Z���^�[�X�N���[��)
#define BG_STAGE_WIDTH				(300)										// BG�e�N�X�`������
#define BG_STAGE_HEIGHT				(250)										// BG�e�N�X�`������
#define BG_FADE_SPEED				(2)											// �w�i�̃t�F�[�h���x
#define BG_BASE_ALPHA				(1)											// �������l

#define STAGESELECT_TEXT_ONE		"data/TEXTURE/STAGEVIEW/StageLogo000.png"	// �X�e�[�W�Z���N�g�e�N�X�`���F�X�e�[�W�P
#define STAGESELECT_TEXT_TWO		"data/TEXTURE/STAGEVIEW/StageLogo01.png"	// �X�e�[�W�Z���N�g�e�N�X�`���F�X�e�[�W�P
#define STAGESELECT_TEXT_THREE		"data/TEXTURE/STAGEVIEW/StageLogo02.png"	// �X�e�[�W�Z���N�g�e�N�X�`���F�X�e�[�W�P
#define STAGESELECT_TEXT_FOUR		"data/TEXTURE/STAGEVIEW/StageLogo03.png"	// �X�e�[�W�Z���N�g�e�N�X�`���F�X�e�[�W�P
#define STAGESELECT_TEX_SELECT_SIZE	D3DXVECTOR2(280.0f, 90.0f)				// �I���������̃e�N�X�`���̑傫��
#define STAGESELECT_TEX_SIZE		D3DXVECTOR2(24
0.0f, 40.0f)					// �����e�N�X�`���̑傫��
#define FLAME_TEX_X					(0.69f)										// ������x���z�u�{��

#define STAGESELECT_TEX_FLAME      "data/TEXTURE/UI/Frame00.png"		// �X�e�[�W�Z���N�g�̃t���[���e�N�X�`��
#define STAGESELECT_SELECT_SIZE		D3DXVECTOR2(280.0f, 100.0f)			// �I���������̃e�N�X�`���̑傫��
#define STAGESELECT_FLAME_SIZE		D3DXVECTOR2(240.0f, 60.0f)			// �t���[���e�N�X�`���̑傫��
#define FLAME_POS_X					(0.7f)								// �t���[����x���z�u�{��
#define FLAME_POS_X_PLUS			(0.05f)								// �t���[����x���z�u�{�������l
#define FLAME_POS_Y_PLUS			(120.0f)							// �t���[����y���z�u�{�������l

// �X�e�[�W�Z���N�g�}�N��
enum STATUSSTAGESELECT
{
	SSS_TUTORIAL = 0,				// �`���[�g���A��
	SSS_GRASS,						// ����
	SSS_SEASHORE,					// �C��
	SSS_CRYSTAL,					// �N���X�^���̐X
	SSS_MAX
};

// �o�����Z���N�g�}�N��
enum STATUSSTAGEROT
{
	ROT_DOWN = -1,	// �_�E��
	ROT_SELECT,		// �Z���N�g
	ROT_UP,			// �A�b�v
	ROT_MAX			// �o�����Z���N�g�ő吔
};


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

/*�Z���N�g�w�i�N���X */
class StageSelectBg : public C2DObject
{
public:
	StageSelectBg() {};			// �R���X�g���N�^
	~StageSelectBg() {};		// �f�X�g���N�^

	// �w�i�t�F�[�h�C���֐�
	void BgSetAlpha(int alpha)
	{

		// ���l�𔽉f
		Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);
		Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, alpha);

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
