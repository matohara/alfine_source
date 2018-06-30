//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.cpp]
// Author : ���ˌ��j��
//
//=============================================================================
#include "title.h"
#include "../../input.h"
#include "fade.h"
#include "../../DebugProcess.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGESELECT_TEX_TUTORIAL      "data/TEXTURE/STAGEVIEW/Tutorial.jpg"
#define STAGESELECT_TEX_TUTORIAL_LOGO "data/TEXTURE/STAGEVIEW/TutorialLogo.png"

#define STAGESELECT_TEX_FLAME      "data/TEXTURE/UI/Frame00.png"				// �X�e�[�W�Z���N�g�̃t���[���e�N�X�`��
#define STAGESELECT_SELECT_SIZE		D3DXVECTOR2(280.0f, 100.0f)					// �I���������̃e�N�X�`���̑傫��
#define STAGESELECT_FLAME_SIZE		D3DXVECTOR2(240.0f, 60.0f)					// �t���[���e�N�X�`���̑傫��
#define FLAME_POS_X					(0.7f)										// �t���[����x���z�u�{��
#define FLAME_POS_X_PLUS			(0.05f)										// �t���[����x���z�u�{�������l
#define FLAME_POS_Y_PLUS			(120.0f)										// �t���[����y���z�u�{�������l

#define STAGESELECT_TEXT	      "data/TEXTURE/UI/Stage_Tex.png"				// �X�e�[�W�Z���N�g�̃t���[���e�N�X�`��

// �X�e�[�W�Z���N�g�}�N��
enum STATUSSTAGESELECT
{
	SSS_TUTORIAL = 0,				// �`���[�g���A��
	SSS_GRASS,						// ����
	SSS_SEASHORE,					// �C��
	SSS_CRYSTAL,					// �N���X�^���̐X
	SSS_MAX
};

// �o�����Z���N�g�}�N��
enum STATUSSTAGEROT
{
	ROT_DOWN=-1,	// �_�E��
	ROT_SELECT,		// �Z���N�g
	ROT_UP,			// �A�b�v
	ROT_MAX			// �o�����Z���N�g�ő吔
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
C2DUIPolygonA StageSelectBack;
C2DUIMenuLogo StageSelectText;
C2DUIMenuLogo StageSelectLogo[SSS_MAX];				// �X�e�[�W�Z���N�g�ő吔�錾
STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;
int 			SSSflag[SSS_MAX];					// �o�����t���O�Ǘ��ϐ�
int				SELECTflag;							// �Z���N�g�t���O
bool			UPflag;								// ��ړ��t���O
bool			DOWNflag;							// ���ړ��t���O

D3DXVECTOR2 selectsize;			// �I���������̃t���[���̑傫��
D3DXVECTOR2 flamesize;			// �t���[���̑傫��
D3DXVECTOR2 speed;				// �t���[���ړ���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStageSelect(void)
{

	// �w�i�e�N�X�`��
	StageSelectBack.Init(STAGESELECT_TEX_TUTORIAL);

	//�t���[���T�C�Y�̏�����
	selectsize = STAGESELECT_SELECT_SIZE;	// �I���������̃t���[���̑傫��
	flamesize = STAGESELECT_FLAME_SIZE;		// �t���[���̑傫��

	// �ړ��ʂ��i�[
	speed.x = RelativeSX(FLAME_POS_X_PLUS);
	speed.y = FLAME_POS_Y_PLUS;

	// �Z���N�g�t���O��I�𒆂ŏ�����
	SELECTflag = ROT_SELECT;

	// ��ړ��𖢎g�p�ŏ�����
	UPflag = false;

	// ���ړ����g�p�ŏ�����
	DOWNflag = true;

	// �����e�N�X�`��
	StageSelectText.Init(selectsize.x,				// �e�N�X�`���̉���
						selectsize.y+30,				// �e�N�X�`���̏c��
						RelativeSX(FLAME_POS_X),	// �z�u�ʒuX��
						SCREEN_CENTER_Y,			// �z�u�ʒuY��
						STAGESELECT_TEXT);			// �ǂݍ��ރe�N�X�`��

	// �X�e�[�W�Z���N�g�e�N�X�`���ő吔������
	for (int i = 0;i < SSS_MAX;i++)
	{

		// �I������Ă���t���[�������g��
		if (i == SSS_TUTORIAL)
		{

			// �I������Ă���
			SSSflag[i] = ROT_SELECT;

			// ���N�����̓`���[�g���A����I��
			StageSelectLogo[SSS_TUTORIAL].Init(selectsize.x,				// �t���[���e�N�X�`���̉���
											   selectsize.y,				// �t���[���e�N�X�`���̏c��
											   RelativeSX(FLAME_POS_X),		// �z�u�ʒuX��
											   SCREEN_CENTER_Y,				// �z�u�ʒuY��
											   STAGESELECT_TEX_FLAME);		// �ǂݍ��ރe�N�X�`��
		}

		// ����ȊO�͊g�喳��
		else
		{

			// �I������Ă���t���[����艺��
			SSSflag[i] = ROT_DOWN;

			// �t���[���̏�����
			StageSelectLogo[i].Init(flamesize.x,										// �t���[���e�N�X�`���̉���
									flamesize.y,										// �t���[���e�N�X�`���̏c��
									RelativeSX((FLAME_POS_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX�� (FLAME_POS_X_PLUS*i)�����
									SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),				// �z�u�ʒuY�� (FLAME_POS_Y_PLUS*i)�����
									STAGESELECT_TEX_FLAME);								// �ǂݍ��ރe�N�X�`��

			// ���I��F
			StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.ReleaseBuffer();

	// �X�e�[�W�Z���N�g�ő吔���������
	for (int i = 0;i < SSS_MAX;i++)
	{
		StageSelectLogo[i].ReleaseBuffer();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageSelect(void)
{

	// �X�e�[�W�Z���N�g�ő吔�X�V����
	for (int i = 0;i < SSS_MAX;i++)
	{
		// �G���^�[�L�[�������ꂽ��
		if ((GetKeyboardTrigger(DIK_RETURN)) || (IsButtonTriggered(0, BUTTON_X)))
		{
			// �X�e�[�W�Z���N�g
			switch (SSStastus)
			{
			// �`���[�g���A��
			case SSS_TUTORIAL:

				// ��ʑJ��:�`���[�g���A��
				CSFade::SetFade(SCENE_GAME);
				break;
			}
		}

		// ���L�[����������
		else if ((GetKeyboardTrigger(DIK_UP)) || (IsButtonTriggered(0, LSTICK_UP)))
		{
			// ��ړ��\�Ȃ��
			if (UPflag == true)
			{
				// �I���t���[������̏ꍇ
				if (SSSflag[i] == ROT_UP)
				{
					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x -= speed.x;
					StageSelectLogo[i].Position.y += speed.y;

					// �Z���N�g�t���O�A�܂��͈���̃t���O���I�𒆂�������
					if ((SELECTflag == ROT_SELECT) || (SSSflag[i + 1] == ROT_SELECT))
					{
						// �e�N�X�`���T�C�Y�g��
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);

						// �J���[�ύX
						StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						// �t���O��I���t���[����
						SSSflag[i] = ROT_SELECT;

					}

					else
					{
						// �e�N�X�`���X�V
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					}

					// �Z���N�g�t���O���t���[�����
					SELECTflag = ROT_UP;
				}

				// �I���t���[����艺�̏ꍇ
				else if (SSSflag[i] == ROT_DOWN)
				{
					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y += speed.y;


					// �e�N�X�`���X�V
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);


					// �Z���N�g�t���O���t���[������
					SELECTflag = ROT_DOWN;
				}

				// �I������Ă���t���[���Ȃ�
				else if (SSSflag[i] == ROT_SELECT)
				{

					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y += speed.y;

					// �e�N�X�`���T�C�Y�k��
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);

					// �J���[�ύX
					StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					// �Ōオ�I������Ă���ꍇ
					if (i == SSS_CRYSTAL)
					{
						// �Z���N�g�t���O��I�𒆂�
						SELECTflag = ROT_DOWN;
					}
					// ����ȊO
					else
					{
						// �Z���N�g�t���O��I�𒆂�
						SELECTflag = ROT_SELECT;
					}

					// �t���O��I���t���[������
					SSSflag[i] = ROT_DOWN;

				}
			}

		}


		// ���L�[����������z
		else if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
		{
			// ���ړ��\�Ȃ��
			if (DOWNflag == true)
			{

				// �I���t���[������̏ꍇ
				if (SSSflag[i] == ROT_UP)
				{
					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y -= speed.y;


					// �e�N�X�`���X�V
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);


					// �Z���N�g�t���O���t���[�����
					SELECTflag = ROT_UP;
				}

				// �I���t���[����艺�̏ꍇ
				else if (SSSflag[i] == ROT_DOWN)
				{
					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x -= speed.x;
					StageSelectLogo[i].Position.y -= speed.y;


					// �Z���N�g�t���O��I�𒆂�������
					if (SELECTflag == ROT_SELECT)
					{
						// �e�N�X�`���T�C�Y�g��
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y - selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + selectsize.x, StageSelectLogo[i].Position.y + selectsize.y, 0.0f);

						// �J���[�ύX
						StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						// �t���O��I���t���[����
						SSSflag[i] = ROT_SELECT;

					}

					else
					{
						// �e�N�X�`���X�V
						StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
						StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					}


					// �Z���N�g�t���O���t���[������
					SELECTflag = ROT_DOWN;

				}

				// �I������Ă���t���[���Ȃ�
				else if (SSSflag[i] == ROT_SELECT)
				{
					// �ړ��ʂ��X�V
					StageSelectLogo[i].Position.x += speed.x;
					StageSelectLogo[i].Position.y -= speed.y;

					// �e�N�X�`���T�C�Y�k��
					StageSelectLogo[i].Vertex[0].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[1].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y - flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[2].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x - flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);
					StageSelectLogo[i].Vertex[3].vtx = D3DXVECTOR3(StageSelectLogo[i].Position.x + flamesize.x, StageSelectLogo[i].Position.y + flamesize.y, 0.0f);

					// �J���[�ύX
					StageSelectLogo[i].Vertex[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					StageSelectLogo[i].Vertex[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					// �Z���N�g�t���O��I�𒆂�
					SELECTflag = ROT_SELECT;

					// �t���O��I���t���[�����
					SSSflag[i] = ROT_UP;

				}
			}

		}


	}


	// ���ړ����䏈��
	// �Ō�̏�����������
	// ���L�[����������
	if ((GetKeyboardTrigger(DIK_UP)) || (IsButtonTriggered(0, LSTICK_UP)))
	{
		// ��ړ����䏈��
		// �ŏ��̏�����������
		if (SSSflag[SSS_TUTORIAL] == ROT_SELECT)
		{
			// ��ړ�����
			UPflag = false;
		}
		// ����ȊO
		else
		{
			// ��ړ��\
			DOWNflag = true;
		}

	}
	// ���L�[����������
	else if if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
	{

		if (SSSflag[SSS_CRYSTAL] == ROT_SELECT)
		{
			// ���ړ�����
			DOWNflag = false;
		}

		// ����ȊO
		else
		{
			// ���ړ��\
			UPflag = true;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStageSelect(void)
{

	// �w�i�`��
	StageSelectBack.Draw();

	// �X�e�[�W�Z���N�g�ő吔�`�揈��
	for (int i = 0;i < SSS_MAX;i++)
	{
		StageSelectLogo[i].Draw();
	}

	// �����`��
	StageSelectText.Draw();

}

