//=============================================================================
//
// ゲームステージ管理 [Stage.cpp]
// Author : 初 景新
//
//=============================================================================
#include "Stage.h"

/* ステージファイル */
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


