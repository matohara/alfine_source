//=============================================================================
//
// ���[�f�B���O��ʏ��� [Loading.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _LOADING_INCLUDE_H_
#define _LOADING_INCLUDE_H_

#include "../../main.h"
#include "../class/ObjectBase.h"

//*****************************************************************************
// �N���X�݌v
//*****************************************************************************
class CNowLoading
{
//	GAMESCENE NextScene;

public:
	C2DUIPolygon Back;
	C2DUIPolygon Text;
	C2DUIPercentGauge PercentGage;

	void Init(GAMESCENE scene);
	void Uninit(void);
	void Progress(int per);

private:

};



#endif
