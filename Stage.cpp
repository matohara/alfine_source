//=============================================================================
//
// �Q�[���X�e�[�W�Ǘ� [Stage.cpp]
// Author : �� �i�V
//
//=============================================================================
#include "Stage.h"

/* �X�e�[�W�t�@�C�� */
#include "Stage/STutorial.h"
#include "Stage/Stage01.h"


StageBase *RunStage = NULL;

void SetRunStage(StageBase *stage)
{
	if (RunStage != NULL)
	{
		delete RunStage;
		RunStage = NULL;
	}
	RunStage = stage;
}

StageBase *GetRunStage()
{
	return new Stage01;
}


