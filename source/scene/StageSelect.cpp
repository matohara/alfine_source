//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "title.h"
#include "../../input.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/Tutorial.jpg"
#define STAGESELECT_TEX_TUTORIAL_LOGO "data/TEXTURE/STAGEVIEW/TutorialLogo.png"

enum STATUSSTAGESELECT
{
	SSS_TUTORIAL = 0,
	SSS_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
C2DUIPolygon StageSelectBack;
C2DUIPolygon StageSelectLogo;
STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStageSelect(void)
{
	StageSelectBack.Init(STAGESELECT_TEX_TUTORIAL);
	StageSelectLogo.Init(240, 60, RelativeSX(0.7f), SCREEN_CENTER_Y, STAGESELECT_TEX_TUTORIAL_LOGO);	// 1024 : 256 (4)

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.ReleaseBuffer();
	StageSelectLogo.ReleaseBuffer();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageSelect(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		switch (SSStastus)
		{
		case SSS_TUTORIAL:
			CSFade::SetFade(SCENE_GAME);
			break;
		}
	}

	if (GetKeyboardTrigger(DIK_UP))
	{

	}

	if (GetKeyboardTrigger(DIK_DOWN))
	{

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStageSelect(void)
{
	StageSelectBack.Draw();
	StageSelectLogo.Draw();
}

