#ifndef _STAGE_TUTORIAL_
#define _STAGE_TUTORIAL_

#include "StageBase.h"

/* TutorialText */
#define TUTORIAL_UI01 "data/�`���[�g���A��/Text00.png"
#define TUTORIAL_UI02 "data/�`���[�g���A��/Text01.png"
#define TUTORIAL_UI03 "data/�`���[�g���A��/Text02.png"
#define TUTORIAL_UI11 "data/�`���[�g���A��/Text10.png"
#define TUTORIAL_UI12 "data/�`���[�g���A��/Text11.png"
#define TUTORIAL_UI13 "data/�`���[�g���A��/Text12.png"

#define TUTORIAL_UI21 "data/�`���[�g���A��/Text21.png"
#define TUTORIAL_UI22 "data/�`���[�g���A��/Text22.png"
#define TUTORIAL_UI23 "data/�`���[�g���A��/Text23.png"

#define TUTORIAL_UI31 "data/�`���[�g���A��/poipoi2.png"


/* TutorialObject */
#define TUTORIAL_OBJ01 "data/�`���[�g���A��/obj01.png"

class STutorial : public StageBase
{
	LPDIRECT3DTEXTURE9    TutorialObjTex = NULL;
	C3DMultiPolygonObject TutorialObjON[8][2];
	C3DMultiPolygonObject TutorialObjOF[8][2];

	C3DCubeObject TestCube;

public:
	STutorial()
	{

	}

	int  Init()
	{
		TestCube.LoadTexture(TUTORIAL_OBJ01);
		TestCube.Init(DXV3(0.0f, 100.0f, 0.0f), 100.0f);

		// �I�u�W�F�N�g
		D3DXCreateTextureFromFile(GetDevice(), TUTORIAL_OBJ01, &TutorialObjTex);
		for (int i = 0; i < 8; i++)
		{
			TutorialObjOF[i][0].LoadTexture(TutorialObjTex);
			TutorialObjOF[i][1].LoadTexture(TutorialObjTex);
			TutorialObjON[i][0].LoadTexture(TutorialObjTex);
			TutorialObjON[i][1].LoadTexture(TutorialObjTex);
		}

		int cnt = 0;
		float posX = 0.0f;
		for (int i = 0; i < 8; i++)
		{
			posX = (float)(GameSystem::Notes[cnt].Timing * 3 + 30 + 50);
			TutorialObjON[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), D3DXVECTOR2(50, 50));
			posX -= 45.0f;
			TutorialObjON[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR2(50, 50));
			cnt++;

			posX = (float)(GameSystem::Notes[cnt].Timing * 3 + 30 + 50);
			TutorialObjOF[i][0].Init(D3DXVECTOR3(posX, 50.0f, -100.0f), D3DXVECTOR2(50, 50));
			posX -= 45.0f;
			TutorialObjOF[i][1].Init(D3DXVECTOR3(posX, 50.0f, -50.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR2(50, 50));
			cnt++;
		}

	}
	int  Update()
	{

	}
	void Draw()
	{
		TestCube.Draw();

		// �I�u�W�F�N�g
		if (SetGameFlag(FLAG_GAME_MAPSIDES, FT_CHECK))
		{
			for (int i = 0; i < 8; i++)
			{
				TutorialObjOF[i][0].Draw();
				TutorialObjOF[i][1].Draw();
			}
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				TutorialObjON[i][0].Draw();
				TutorialObjON[i][1].Draw();
			}
		}
	}
	void Uninit()
	{
		TestCube.Release();

		if (TutorialObjTex != NULL)
		{
			TutorialObjTex->Release();
			TutorialObjTex = NULL;
		}

		for (int i = 0; i < 8; i++)
		{
			TutorialObjON[i][0].Release();
			TutorialObjON[i][1].Release();
			TutorialObjOF[i][0].Release();
			TutorialObjOF[i][1].Release();
		}
	}


private:

};




#endif // !_STAGE_TUTORIAL_
