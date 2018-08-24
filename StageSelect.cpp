//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.cpp]
// Author : ���ˌ��j��
//
//=============================================================================
#include "title.h"
#include "StageSelect.h"
#include "Library\Input.h"
#include "Library\Fade.h"
#include "Library\Sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void BgmStageSelect(int cnt);			// �Z���N�g���y�֐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UIBackGround	StageSelectBack;					// �w�i�i�[�ϐ�
Barrel			StageSelectText[SSS_MAX];			// �X�e�[�W�Z���N�g���b�Z�[�W
StageSelectBg	SelectBg[SSS_MAX];					// �X�e�[�W�Z���N�g�w�i
Barrel			StageSelectLogo[SSS_MAX];			// �X�e�[�W�Z���N�g�ő吔�錾
C2DObject		StageSelectUi;						// �X�e�[�W�Z���N�gUI

STATUSSTAGESELECT SSStastus = SSS_TUTORIAL;
int 			SSSflag[SSS_MAX];					// �o�����t���O�Ǘ��ϐ�
int				SELECTflag;							// �Z���N�g�t���O
int				SelectAlpha;						// ���l����ϐ�
bool			UPflag;								// ��ړ��t���O
bool			DOWNflag;							// ���ړ��t���O

D3DXVECTOR2 selectsize;			// �I���������̃t���[���̑傫��
D3DXVECTOR2 flamesize;			// �t���[���̑傫��
D3DXVECTOR2 selectTexSize;		// �I���������̕����̑傫��
D3DXVECTOR2 texSize;			// �����̑傫��
D3DXVECTOR2 speed;				// �t���[���ړ���

DSound SelectBGM[SSS_MAX];		// �Z���N�gBGM

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStageSelect(void)
{

	// BGM
	SelectBGM[SSS_TUTORIAL].LoadSound("data/BGM/���j���[�E�`���[�g���A��.wav");	// �`���[�g���A��
	SelectBGM[SSS_GRASS].LoadSound("data/BGM/���j���[�E����.wav");				// �X�e�[�W�P
	SelectBGM[SSS_SEASHORE].LoadSound("data/BGM/���j���[�E�C.wav");				// �X�e�[�W�Q
	SelectBGM[SSS_CRYSTAL].LoadSound("data/BGM/���j���[�E����.wav");			// �X�e�[�W�R


	// �w�i�e�N�X�`��
	StageSelectBack.LoadTexture(STAGESELECT_TEX_TUTORIAL);

	//�t���[���T�C�Y�̏�����
	selectsize = STAGESELECT_SELECT_SIZE;		// �I���������̃t���[���̑傫��
	flamesize = STAGESELECT_FLAME_SIZE;			// �t���[���̑傫��

	//�����T�C�Y�̏�����
	selectTexSize = STAGESELECT_TEX_SELECT_SIZE;	// �I���������̕����̑傫��
	texSize = STAGESELECT_TEX_SIZE;					// �����̑傫��


	// �ړ��ʂ��i�[
	speed.x = RelativeSX(FLAME_POS_X_PLUS);
	speed.y = FLAME_POS_Y_PLUS;

	// �Z���N�g�t���O��I�𒆂ŏ�����
	SELECTflag = ROT_SELECT;

	// ���l�̏�����
	SelectAlpha = BG_BASE_ALPHA;

	// ��ړ��𖢎g�p�ŏ�����
	UPflag = false;

	// ���ړ����g�p�ŏ�����
	DOWNflag = true;

	// UI�e�N�X�`��
	StageSelectUi.Init( 320,							// �z�u�ʒuX��
						545,							// �z�u�ʒuY��
						320,							// �e�N�X�`���̉���
						150,							// �e�N�X�`���̏c��
						STAGESELECT_TEX_UI);			// �ǂݍ��ރe�N�X�`��



	// �X�e�[�W�Z���N�g�e�N�X�`���ő吔������
	for (int i = 0;i < SSS_MAX;i++)
	{


		// �I������Ă���t���[�������g��
		if (i == SSS_TUTORIAL)
		{

			// �I������Ă���
			SSSflag[i] = ROT_SELECT;

			// ���N�����̓`���[�g���A����I��
			SelectBg[i].Init(BG_STAGE_POS_X,				// �z�u�ʒuX��
										SCREEN_CENTER_Y,			// �z�u�ʒuY��
										BG_STAGE_WIDTH,				// �t���[���e�N�X�`���̉���
										BG_STAGE_HEIGHT,			// �t���[���e�N�X�`���̏c��
										BG_STAGE_ONE);				// �ǂݍ��ރe�N�X�`��

			// ���N�����̓`���[�g���A����I��
			StageSelectLogo[i].Init(RelativeSX(FLAME_POS_X),		// �z�u�ʒuX��
											   SCREEN_CENTER_Y,				// �z�u�ʒuY��
											   selectsize.x,				// �t���[���e�N�X�`���̉���
											   selectsize.y,				// �t���[���e�N�X�`���̏c��
											   STAGESELECT_TEX_FLAME);		// �ǂݍ��ރe�N�X�`��

			// �����e�N�X�`��
			StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX��
												SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// �z�u�ʒuY��
												selectTexSize.x,						// �e�N�X�`���̉���
												selectTexSize.y,						// �e�N�X�`���̏c��
												STAGESELECT_TEXT_ONE);					// �ǂݍ��ރe�N�X�`��

		}

		// ����ȊO�͊g�喳��
		else
		{
			// �X�e�[�W1
			if (i == SSS_GRASS)
			{
				SelectBg[i].Init(BG_STAGE_POS_X,			// �z�u�ʒuX��
								SCREEN_CENTER_Y,			// �z�u�ʒuY��
								BG_STAGE_WIDTH,				// �t���[���e�N�X�`���̉���
								BG_STAGE_HEIGHT,			// �t���[���e�N�X�`���̏c��
								BG_STAGE_TWO);				// �ǂݍ��ރe�N�X�`��

															// �����e�N�X�`��
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX��
										SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// �z�u�ʒuY��
										texSize.x,						// �e�N�X�`���̉���
										texSize.y,						// �e�N�X�`���̏c��
										STAGESELECT_TEXT_TWO);					// �ǂݍ��ރe�N�X�`��


			}

			// �X�e�[�W2
			else if (i == SSS_SEASHORE)
			{
				SelectBg[i].Init(BG_STAGE_POS_X,			// �z�u�ʒuX��
								SCREEN_CENTER_Y,			// �z�u�ʒuY��
								BG_STAGE_WIDTH,				// �t���[���e�N�X�`���̉���
								BG_STAGE_HEIGHT,			// �t���[���e�N�X�`���̏c��
								BG_STAGE_THREE);			// �ǂݍ��ރe�N�X�`��

															// �����e�N�X�`��
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX��
					SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// �z�u�ʒuY��
					texSize.x,						// �e�N�X�`���̉���
					texSize.y,						// �e�N�X�`���̏c��
					STAGESELECT_TEXT_THREE);					// �ǂݍ��ރe�N�X�`��


			}

			// �X�e�[�W3
			else if (i == SSS_CRYSTAL)
			{
				// ���N�����̓`���[�g���A����I��
				SelectBg[i].Init(BG_STAGE_POS_X,				// �z�u�ʒuX��
								SCREEN_CENTER_Y,				// �z�u�ʒuY��
								BG_STAGE_WIDTH,					// �t���[���e�N�X�`���̉���
								BG_STAGE_HEIGHT,				// �t���[���e�N�X�`���̏c��
								BG_STAGE_FOUR);					// �ǂݍ��ރe�N�X�`��

																// �����e�N�X�`��
				StageSelectText[i].Init(RelativeSX((FLAME_TEX_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX��
					SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),	// �z�u�ʒuY��
					texSize.x,						// �e�N�X�`���̉���
					texSize.y,						// �e�N�X�`���̏c��
					STAGESELECT_TEXT_FOUR);					// �ǂݍ��ރe�N�X�`��


			}



			// �I������Ă���t���[����艺��
			SSSflag[i] = ROT_DOWN;

			// �t���[���̏�����
			StageSelectLogo[i].Init(RelativeSX((FLAME_POS_X + (FLAME_POS_X_PLUS * i))),	// �z�u�ʒuX�� (FLAME_POS_X_PLUS*i)�����
									SCREEN_CENTER_Y + (FLAME_POS_Y_PLUS*i),				// �z�u�ʒuY�� (FLAME_POS_Y_PLUS*i)�����
									flamesize.x,										// �t���[���e�N�X�`���̉���
									flamesize.y,										// �t���[���e�N�X�`���̏c��
									STAGESELECT_TEX_FLAME);								// �ǂݍ��ރe�N�X�`��

			// ���I��F
			StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStageSelect(void)
{
	StageSelectBack.Release();

	// �X�e�[�W�Z���N�gUI
	StageSelectUi.Release();


	// �X�e�[�W�Z���N�g�ő吔���������
	for (int i = 0;i < SSS_MAX;i++)
	{

		// �X�e�[�W�Z���N�g���b�Z�[�W
		StageSelectText[i].Release();

		// �X�e�[�W�Z���N�g�w�i
		SelectBg[i].Release();

		// �X�e�[�W�Z���N�g
		StageSelectLogo[i].Release();

		// �Z���N�g���y
		SelectBGM[i].Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageSelect(void)
{
	
	// ����L�[�������ꂽ��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		CSFade::SetFade(SCENE_GAME);
	}

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

			// �ʒu�X�V�p�ϐ���錾
			D3DXVECTOR2 move;

			// �ϐ��̏�����
			move.x = 0;
			move.y = 0;

			// ��ړ��\�Ȃ��
			if (UPflag == true)
			{

				// ���l�̏�����
				SelectAlpha = BG_BASE_ALPHA;

				// �I���t���[������̏ꍇ
				if (SSSflag[i] == ROT_UP)
				{
					// �ړ��ʂ��X�V
					move.x -= speed.x;
					move.y += speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					// �Z���N�g�t���O�A�܂��͈���̃t���O���I�𒆂�������
					if ((SELECTflag == ROT_SELECT) || (SSSflag[i + 1] == ROT_SELECT))
					{
						// �e�N�X�`���T�C�Y�g��
						StageSelectLogo[i].LogoSize(selectsize.x, selectsize.y);

						// �J���[�ύX
						StageSelectLogo[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// �����T�C�Y�g��
						StageSelectText[i].LogoSize(selectTexSize.x, selectTexSize.y);

						// �����J���[�ύX
						StageSelectText[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// �t���O��I���t���[����
						SSSflag[i] = ROT_SELECT;

						// BGM�ύX
						BgmStageSelect(i);

					}

					else
					{
						// �e�N�X�`���X�V
						StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
						StageSelectText[i].LogoSize(texSize.x, texSize.y);		// ����


					}

					// �Z���N�g�t���O���t���[�����
					SELECTflag = ROT_UP;
				}

				// �I���t���[����艺�̏ꍇ
				else if (SSSflag[i] == ROT_DOWN)
				{
					// �ړ��ʂ��X�V
					move += speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					// �e�N�X�`���X�V
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
					StageSelectText[i].LogoSize(texSize.x,texSize.y);		// ����


					// �Z���N�g�t���O���t���[������
					SELECTflag = ROT_DOWN;
				}

				// �I������Ă���t���[���Ȃ�
				else if (SSSflag[i] == ROT_SELECT)
				{

					// �ړ��ʂ��X�V
					move += speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					// �e�N�X�`���T�C�Y�k��
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// ����

					// �J���[�ύX
					StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// �t���[��
					StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// ����


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

			// �ʒu�X�V�p�ϐ���錾
			D3DXVECTOR2 move;

			// �ϐ��̏�����
			move.x = 0;
			move.y = 0;

			// ���ړ��\�Ȃ��
			if (DOWNflag == true)
			{

				// ���l�̏�����
				SelectAlpha = BG_BASE_ALPHA;

				// �I���t���[������̏ꍇ
				if (SSSflag[i] == ROT_UP)
				{
					// �ړ��ʂ��X�V
					move.x += speed.x;
					move.y -= speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					// �e�N�X�`���X�V
					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// ����

					// �Z���N�g�t���O���t���[�����
					SELECTflag = ROT_UP;
				}

				// �I���t���[����艺�̏ꍇ
				else if (SSSflag[i] == ROT_DOWN)
				{
					// �ړ��ʂ��X�V
					move -= speed;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					// �Z���N�g�t���O��I�𒆂�������
					if (SELECTflag == ROT_SELECT)
					{
						// �e�N�X�`���T�C�Y�g��
						StageSelectLogo[i].LogoSize(selectsize.x, selectsize.y);

						// �J���[�ύX
						StageSelectLogo[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// �����T�C�Y�g��
						StageSelectText[i].LogoSize(selectTexSize.x, selectTexSize.y);

						// �����J���[�ύX
						StageSelectText[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

						// �t���O��I���t���[����
						SSSflag[i] = ROT_SELECT;

						// BGM�ύX
						BgmStageSelect(i);

					}

					else
					{
						// �e�N�X�`���X�V
						StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
						StageSelectText[i].LogoSize(texSize.x, texSize.y);		// ����

					}


					// �Z���N�g�t���O���t���[������
					SELECTflag = ROT_DOWN;

				}

				// �I������Ă���t���[���Ȃ�
				else if (SSSflag[i] == ROT_SELECT)
				{
					// �ړ��ʂ��X�V
					move.x += speed.x;
					move.y -= speed.y;
					StageSelectLogo[i].LogoMove(move.x, move.y);	// �t���[��
					StageSelectText[i].LogoMove(move.x, move.y);	// ����

					StageSelectLogo[i].LogoSize(flamesize.x, flamesize.y);	// �t���[��
					StageSelectText[i].LogoSize(texSize.x, texSize.y);		// ����

					// �J���[�ύX
					StageSelectLogo[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// �t���[��
					StageSelectText[i].SetVertex(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));	// ����

					// �Z���N�g�t���O��I�𒆂�
					SELECTflag = ROT_SELECT;

					// �t���O��I���t���[�����
					SSSflag[i] = ROT_UP;
				}
			}
		}

		// �t�F�[�h����
		// �I��w�i�t�F�[�h�C��
		SelectBg[i].BgSetAlpha(SelectAlpha);

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
	else if ((GetKeyboardTrigger(DIK_DOWN)) || (IsButtonTriggered(0, LSTICK_DOWN)))
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

	// ���l���Z
	// ���l�����E�l�𒴂��Ă��Ȃ����
	if (SelectAlpha < 255)
	{
		// ���l�����Z
		SelectAlpha += BG_FADE_SPEED;
	}
	// �����Ă�����
	else
	{
		SelectAlpha = 255;
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

		// �I������Ă���ꍇ�\��
		if (SSSflag[i] == ROT_SELECT)
		{
			// �I��w�i�`��
			SelectBg[i].Draw();

		}

		// �e�N�X�`���t���[���`��
		StageSelectLogo[i].Draw();

		// �����`��
		StageSelectText[i].Draw();

	}

	// UI�`��
	StageSelectUi.Draw();


}

//=============================================================================
// ���y�I������
//=============================================================================
void BgmStageSelect(int cnt)
{

	// �X�e�[�W�Z���N�g�ő吔����
	for (int i = 0;i < SSS_MAX;i++)
	{
		// �I������Ă��������̂��~�߂�
		SelectBGM[i].Stop();

		// �I�����y�Đ�
		if (i == cnt)
		{
			SelectBGM[i].Play(E_DS8_FLAG_LOOP);

		}
	}

}