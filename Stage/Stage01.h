#ifndef _STAGE_01_
#define _STAGE_01_

#include "StageBase.h"
#include "../Game.h"


enum EGIMMICK
{
	S01_IWA00,
	S01_IWA01,
	S01_JIWARE,
	S01_KAZE,
	S01_KIRIN,
	S01_MIZUUMI00,
	S01_MIZUUMI01,
	S01_RIVER00,
	S01_RIVER01,
	S01_TAIHU00,
	S01_TAIHU01,
	EGIMMICK_MAX
};

enum EOBJECT
{
	S01_LEAF,
	S01_SHEEP,
	S01_SIKA,
	S01_USAGI,
	EOBJECT_MAX
};

class Stage01 : public StageBase
{
	LPDIRECT3DTEXTURE9 GimmickTex[EGIMMICK_MAX] = { NULL };
public:
	Stage01()
	{
		NameTex   = "data/�X�e�[�W1/���S.png";
		ImageTex  = "data/�X�e�[�W1/�C���[�W.png";
		TestMusic = "data/�X�e�[�W1/��.wav";
	}

	int  Init()
	{
		/* �ėp�f�[�^ */
		MusicPassOn  = "data/�X�e�[�W1/�T�E���h/�̂ǂ��ȑ���.wav";
		MusicPassOff = "data/�X�e�[�W1/�T�E���h/�r��̗͋�����_2.wav";
		BackTexOn    = "data/�X�e�[�W1/�t�B�[���h/�w�i�\.jpg";
		BackTexOff   = "data/�X�e�[�W1/�t�B�[���h/�w�i��.jpg";
		FieldTexOn   = "data/�X�e�[�W1/�t�B�[���h/�n�ʕ\.jpg";
		FieldTexOff  = "data/�X�e�[�W1/�t�B�[���h/�n�ʗ�.jpg";

		/* �I�u�W�F�e�N�X�`�� */
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			for (int iCnt = 0; iCnt < EGIMMICK_MAX; iCnt++)
			{
				if (GimmickTex[iCnt] != NULL)
				{	// �e�N�X�`���̊J��
					GimmickTex[iCnt]->Release();
					GimmickTex[iCnt] = NULL;
				}
			}
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Iwa00.png", &GimmickTex[S01_IWA00]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Iwa01.png", &GimmickTex[S01_IWA01]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Jiware.png", &GimmickTex[S01_JIWARE]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Kaze.png", &GimmickTex[S01_KAZE]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Kirin.png", &GimmickTex[S01_KIRIN]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Mizuumi00.png", &GimmickTex[S01_MIZUUMI00]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Mizuumi01.png", &GimmickTex[S01_MIZUUMI01]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/River00.png", &GimmickTex[S01_RIVER00]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/River01.png", &GimmickTex[S01_RIVER01]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Taihu00.png", &GimmickTex[S01_TAIHU00]);
			D3DXCreateTextureFromFile(pDevice, "data/�X�e�[�W1/�M�~�b�N/Taihu01.png", &GimmickTex[S01_TAIHU01]);
		}

		/* �m�[�c */
		SNotes notes[] = {
			{  156, S01_IWA00 },
			{  315, S01_IWA00 },
			{  474, S01_IWA00 },
			{  636, S01_IWA00 },
			{  762, S01_IWA00 },
			{  876, S01_IWA00 },
			{ 1002, S01_IWA00 },
			{ 1194, S01_IWA00 },
			{ 1281, S01_IWA00 },
			{ 1356, S01_IWA00 },
			{ 1518, S01_IWA00 },
			{ 1620, S01_IWA00 },
			{ 1722, S01_IWA00 },
			{ 1836, S01_IWA00 },
			{ 1962, S01_IWA00 },
			{ 2100, S01_IWA00 },
			{ 2241, S01_IWA00 },
			{ 2442, S01_IWA00 },
			{ 2562, S01_IWA00 },
			{ 2718, S01_IWA00 },
			{ 2880, S01_IWA00 },
			{ 2958, S01_IWA00 },
			{ 3078, S01_IWA00 },
			{ 3198, S01_IWA00 },
			{ 3342, S01_IWA00 },
			{ 3441, S01_IWA00 },
			{ 3600, S01_IWA00 },
			{ 3732, S01_IWA00 },
			{ 3894, S01_IWA00 },
			{ 4020, S01_IWA00 },
			{ 4101, S01_IWA00 },
			{ 4239, S01_IWA00 },
			{ 4401, S01_IWA00 },
			{ 4521, S01_IWA00 },
			{ 4638, S01_IWA00 },
			{ 4800, S01_IWA00 } };
		const int nNum = sizeof(notes) / sizeof(SNotes);
		SetNotesData(notes, nNum);

		return 0;
	}

	void Uninit()
	{
		for (int iCnt = 0; iCnt < EGIMMICK_MAX; iCnt++)
		{
			if (GimmickTex[iCnt] != NULL)
			{	// �e�N�X�`���̊J��
				GimmickTex[iCnt]->Release();
				GimmickTex[iCnt] = NULL;
			}
		}
	}

	void SetGimmick(C3DPolygonObject *obj, int timing, int gimmick)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3((float)timing * PLAYER_MOVE_SPEED, GIMMICK_SIZE + 1.0f, -70.0f);
		switch (gimmick)
		{
		case S01_IWA00:
		case S01_IWA01:
		case S01_KAZE:
		case S01_KIRIN:
		case S01_TAIHU00:
		case S01_TAIHU01:
			pos.x += GIMMICK_SIZE + 50.0f;
			obj->LoadTexture(GimmickTex[gimmick]);
			obj->Init(pos, D3DXVECTOR2(GIMMICK_SIZE, GIMMICK_SIZE));
			break;
		case S01_JIWARE:
		case S01_MIZUUMI00:
		case S01_MIZUUMI01:
		case S01_RIVER00:
		case S01_RIVER01:
			pos.x += GIMMICK_SIZE + 50.0f;
			pos.y -= GIMMICK_SIZE;
			obj->LoadTexture(GimmickTex[gimmick]);
			obj->Init(pos, D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f), D3DXVECTOR2(GIMMICK_SIZE, GIMMICK_SIZE));
			break;
		}
	}

};




#endif // !_STAGE_01_
