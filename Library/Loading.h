//=============================================================================
//
// ���[�f�B���O��ʏ��� [Loading.h]
// Author : �� �i�V
//
//=============================================================================
#ifndef _LOADING_INCLUDE_H_
#define _LOADING_INCLUDE_H_


#include "LinkLibrary.h"
#include "ObjectBase2D.h"


class CNowLoading
{
public:
	UIBackGround     Back;
	C2DObject        Text;
	UI2DPercentGauge PercentGage;

	void Init(GAMESCENE scene);
	void Uninit(void);
	void Progress(int per);
};



#endif
