#ifndef _STAGE_02_
#define _STAGE_02_

#include "StageBase.h"
#include "../Game.h"


class Stage02 : public StageBase
{

public:
	Stage02()
	{
		NameTex   = "";
		ImageTex  = "";
		TestMusic = "";
	}

	int  Init()
	{
		MusicPassOn  = "data/ステージ2/サウンド/のどかな草原.wav";
		MusicPassOff = "data/ステージ2/サウンド/荒野の力強さに_2.wav";
		BackTexOn    = "data/ステージ2/フィールド/背景表.jpg";
		BackTexOff   = "data/ステージ2/フィールド/背景裏.jpg";
		FieldTexOn   = "data/ステージ2/フィールド/地面表.jpg";
		FieldTexOff  = "data/ステージ2/フィールド/地面裏.jpg";

		SNotes notes[] = {
			{  240,  },
			{  381,  },
			{  561,  },
			{  639,  },
			{  780,  },
			{  876,  },
			{ 1020,  },
			{ 1200,  },
			{ 1350,  },
			{ 1515,  },
			{ 1740,  },
			{ 1860,  },
			{ 1998,  },
			{ 2136,  },
			{ 2220,  },
			{ 2319,  },
			{ 2475,  },
			{ 2640,  },
			{ 2799,  },
			{ 2940,  },
			{ 3096,  },
			{ 3279,  },
			{ 3438,  },
			{ 3576,  },
			{ 3681,  },
			{ 3840,  },
			{ 3975,  },
			{ 4080,  },
			{ 4200,  },
			{ 4299,  },
			{ 4461,  },
			{ 4635,  },
			{ 4800,  },
			{ 5010,  },
			{ 5121,  } };
		const int nNum = sizeof(notes) / sizeof(SNotes);
		SetNotesData(notes, nNum);

		return 0;
	}

	int  Update()
	{
		return 0;
	}

	void Draw()
	{

	}

	void Uninit()
	{

	}


private:

};




#endif // !_STAGE_02_
