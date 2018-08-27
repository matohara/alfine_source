#ifndef _STAGE_TUTORIAL_
#define _STAGE_TUTORIAL_

#include "StageBase.h"
#include "../Game.h"


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
	LPDIRECT3DTEXTURE9    TutorialObjTex;
	C3DMultiPolygonObject TutorialObjON[8][2];
	C3DMultiPolygonObject TutorialObjOF[8][2];

public:
	STutorial()
	{
		TutorialObjTex = NULL;
		NameTex   = "";
		ImageTex  = "";
		TestMusic = "";
	}

	int  Init()
	{
		MusicPassOn = "data/BGM/tutorial.wav";
		MusicPassOff = "data/BGM/tutorialBack.wav";
		BackTexOn = "data/�`���[�g���A��/OnSideBack.jpg";
		BackTexOff = "data/�`���[�g���A��/OffSideBack.png";
		FieldTexOn = "data/�`���[�g���A��/Field201.jpg";
		FieldTexOff = "data/�`���[�g���A��/Field202.png";

		// �I�u�W�F�N�g
		D3DXCreateTextureFromFile(GetDevice(), TUTORIAL_OBJ01, &TutorialObjTex);
		for (int i = 0; i < 8; i++)
		{
			TutorialObjOF[i][0].LoadTexture(TutorialObjTex);
			TutorialObjOF[i][1].LoadTexture(TutorialObjTex);
			TutorialObjON[i][0].LoadTexture(TutorialObjTex);
			TutorialObjON[i][1].LoadTexture(TutorialObjTex);
		}

		SNotes notes[] = {
			{ 160 },
			{ 240 },
			{ 321 },
			{ 403 },
			{ 484 },
			{ 565 },
			{ 642 },
			{ 704 },
			{ 809 },
			{ 883 },
			{ 962 },
			{ 1083 },
			{ 1184 },
			{ 1281 },
			{ 1362 },
			{ 1442 } };
		const int notesSize = sizeof(notes) / sizeof(SNotes);
		GameSystem::Notes = new SNotes[notesSize];
		for (int iCnt = 0; iCnt < notesSize; iCnt++)
		{
			GameSystem::Notes[iCnt] = notes[iCnt];
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
		return 0;
	}

	int  Update()
	{
		return 0;
	}

	void Draw()
	{
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
