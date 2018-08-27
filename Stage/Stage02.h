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
		MusicPassOn  = "data/�X�e�[�W2/�T�E���h/�̂ǂ��ȑ���.wav";
		MusicPassOff = "data/�X�e�[�W2/�T�E���h/�r��̗͋�����_2.wav";
		BackTexOn    = "data/�X�e�[�W2/�t�B�[���h/�w�i�\.jpg";
		BackTexOff   = "data/�X�e�[�W2/�t�B�[���h/�w�i��.jpg";
		FieldTexOn   = "data/�X�e�[�W2/�t�B�[���h/�n�ʕ\.jpg";
		FieldTexOff  = "data/�X�e�[�W2/�t�B�[���h/�n�ʗ�.jpg";

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
