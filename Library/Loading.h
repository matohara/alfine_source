//=============================================================================
//
// ローディング画面処理 [Loading.h]
// Author : 初 景新
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
