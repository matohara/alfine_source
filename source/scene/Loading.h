//=============================================================================
//
// ローディング画面処理 [Loading.h]
// Author : 初 景新
//
//=============================================================================
#ifndef _LOADING_INCLUDE_H_
#define _LOADING_INCLUDE_H_

#include "../../main.h"
#include "../class/ObjectBase.h"

//*****************************************************************************
// クラス設計
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
