//=============================================================================
//
// �t�F�[�h���� <fade.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "fade.h"


/* �}�N����` */
#define	FADE_RATE		(0.1f)		// �t�F�[�h�W��


/* �O���[�o���ϐ� */
VERTEX_2D	CSFade::Vertex[NUM_VERTEX];
D3DXCOLOR	CSFade::Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
GAMESCENE	CSFade::GameScene;
FADE		CSFade::Fade = FADE_IN;
float		CSFade::Speed = 0.1f;

//----�X�V--------
void CSFade::Update(void)
{
	if(Fade != FADE_NONE)
	{// �t�F�[�h������
		if(Fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			Color.a += Speed;		// ���l�����Z���ĉ�ʂ������Ă���
			if(Color.a > 1.1f)
			{
				// ���[�h��ݒ�
				SetGameScene(GameScene);

				// �t�F�[�h�C�������ɐ؂�ւ�
				Color.a = 1.0f;
				SetFade(FADE_IN, SCENE_MAX, FADE_RATE);
			}

			// �F��ݒ�
			SetColor();
		}
		else if(Fade == FADE_IN)
		{// �t�F�[�h�C������
			Color.a -= Speed;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if(Color.a < 0.0f)
			{
				// �t�F�[�h�����I��
				Color.a = 0.0f;
				SetFade(FADE_NONE, SCENE_MAX, FADE_RATE);
			}

			// �F��ݒ�
			SetColor();
		}
	}
}

//----�`��--------
void CSFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//----���_�쐬--------
void CSFade::MakeVertex(void)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = D3DXVECTOR3(        0.0f,          0.0f, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,          0.0f, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(        0.0f, SCREEN_HEIGHT, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;

	// �e�N�X�`�����W�̐ݒ�
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//----�F��ݒ�--------
void CSFade::SetColor(D3DCOLOR col)
{
	Color = col;
}
void CSFade::SetColor(void)
{
	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//----�t�F�[�h�̐ݒ�--------
void CSFade::SetFade(float spd)
{
	Fade = FADE_OUT;
	GameScene = SCENE_MAX;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(float spd, D3DCOLOR col)
{
	Fade = FADE_OUT;
	GameScene = SCENE_MAX;
	Speed = spd;
	Color = col;
}
void CSFade::SetFade(GAMESCENE scene)
{
	Fade = FADE_OUT;
	GameScene = scene;
	Speed = FADE_RATE;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(GAMESCENE scene, float spd)
{
	Fade = FADE_OUT;
	GameScene = scene;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
void CSFade::SetFade(FADE fade, GAMESCENE scene, float spd)
{
	Fade = fade;
	GameScene = scene;
	Speed = spd;
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//----�t�F�[�h�̏�Ԏ擾--------
FADE CSFade::GetFade(void)
{
	return Fade;
}

