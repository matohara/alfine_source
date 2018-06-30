//=============================================================================
//
// Object-AClass <object.cpp>
// Author : �� �i�V
//
//=============================================================================
#include "Aclass_object.h"


//=============================================================================
// < 3D��{�I�u�W�F�N�g >
// �E�|��
// �EMakeVertex()
// �ELoadTexture()
//=============================================================================

//----�R���X�g���N�^--------
c3DBasicObjectClass::c3DBasicObjectClass()
{
	Texture = NULL;
	VtxBuff = NULL;
}

//----�f�X�g���N�^--------
c3DBasicObjectClass::~c3DBasicObjectClass()
{

}

//----�e�N�X�`����^����--------
void c3DBasicObjectClass::LoadTexture(const char *texture)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}
void c3DBasicObjectClass::LoadTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->Texture = texture;
}


//=============================================================================
// < A�^�I�u�W�F�N�g >
// �E�|��
// �ESetVertex()
//=============================================================================

//----�R���X�g���N�^--------
class_ObjectA::class_ObjectA()
{
	Texture = NULL;		// �e�N�X�`���ւ̃|�C���^
	VtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu���W
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�p�x
	Size = D3DXVECTOR2(0.0f, 0.0f);				// �|���S���T�C�Y
	Scale = 1.0f;								// �T�C�Y�{��

	TexPattern_X = 1;		// �e�N�X�`���p�^�[���i���j
	TexPattern_Y = 1;		// �e�N�X�`���p�^�[���i�c�j
	AnimeCount = 0;			// �A�j���[�V�����J�E���g
	AnimePattern = 0;		// ���݂̃A�j���[�V�����p�^�[���ԍ�
	ChangeAnimeTime = 0;	// �A�j���[�V�����؂�ւ��Ҏ���
}

//----�f�X�g���N�^--------
class_ObjectA::~class_ObjectA()
{

}

//----�`�揈��--------
void class_ObjectA::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// ���e�X�g�ݒ�
	//if (AlphaTestSwitch(0))
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// ��r���郿�̒l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���� (D3DCMP_GREATER)
	}

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�ꍇ������)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�ꍇ������)
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
void class_ObjectA::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// ���e�X�g�ݒ�
	//if (AlphaTestSwitch(0))
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// ��r���郿�̒l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���� (D3DCMP_GREATER)
	}

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�ꍇ������)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O�𖳌��ɂ��� (���C�g�𓖂Ă�ƕςɂȂ�ꍇ������)
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//----�`�揈��(�r���{�[�h)--------
void class_ObjectA::DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld;

	// ���e�X�g�ݒ�
	//if (AlphaTestSwitch(0))
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// ��r���郿�̒l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���� (D3DCMP_GREATER)
	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// �|���S���𐳖ʂɌ�����
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	//D3DXMatrixInverse(&WorldMatrix, NULL, &mtxView);
	//WorldMatrix._41 = 0.0f;
	//WorldMatrix._42 = 0.0f;
	//WorldMatrix._43 = 0.0f;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, Scale, Scale, Scale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
void class_ObjectA::DrawBillboard(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxWorld;

	// ���e�X�g�ݒ�
	//if (AlphaTestSwitch(0))
	{
		// ���e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// ��r���郿�̒l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ���� (D3DCMP_GREATER)
	}

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// �|���S���𐳖ʂɌ�����
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;
	//D3DXMatrixInverse(&WorldMatrix, NULL, &mtxView);
	//WorldMatrix._41 = 0.0f;
	//WorldMatrix._42 = 0.0f;
	//WorldMatrix._43 = 0.0f;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, Scale, Scale, Scale);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//----�`�揈��(Y���r���{�[�h)--------


//----���_�쐬--------
int class_ObjectA::MakeVertex(void)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,		// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,			// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,		// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&VtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))					// NULL�ɐݒ�
	{
		return 1;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}

	return 0;
}

//----���_���W�ݒ�--------
void class_ObjectA::SetVertex(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}
void class_ObjectA::SetVertex(D3DXCOLOR color)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}

//----�o�b�t�@�n�J��--------
void class_ObjectA::ReleaseBuffer(void)
{
	if (Texture != NULL)
	{	// �e�N�X�`���̊J��
		Texture->Release();
		Texture = NULL;
	}

	if (VtxBuff != NULL)
	{	// ���_�̊J��
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}

//----�e�N�X�`����񏑂�����--------
void class_ObjectA::LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = ptnX;
	TexPattern_Y = ptnY;
	ChangeAnimeTime = time;
}
void class_ObjectA::LoadTextureStatus(float sizX, float sizY, float scale)
{
	Size = { sizX, sizY };
	Scale = scale;
	TexPattern_X = 1;
	TexPattern_Y = 1;
	ChangeAnimeTime = 1;
}

//----���E���]--------
void class_ObjectA::FlipX(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3( Size.x,  Size.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-Size.x,  Size.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3( Size.x, -Size.y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuff->Unlock();
	}
}


//=============================================================================
// < P�^�I�u�W�F�N�g >
// �E�|��
//=============================================================================

//----�R���X�g���N�^--------
class_ObjectP::class_ObjectP()
{

}

//----�f�X�g���N�^--------
class_ObjectP::~class_ObjectP()
{

}

//----�`�揈��--------

//----���_�쐬--------


//----���_���W�ݒ�--------
void class_ObjectP::SetVertex(float sizeX, float sizeY)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);

	// ���_�f�[�^���A�����b�N����
	VtxBuff->Unlock();
}


//----�o�b�t�@�n�J��--------



//=============================================================================
// < U�^�I�u�W�F�N�g >
// �E2DUI
// �ELoadTexture()����
//=============================================================================

//----�R���X�g���N�^--------
class_ObjectU::class_ObjectU()
{
	// �e�N�X�`���ւ̃|�C���^
	Texture = NULL;
	// ���_���
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		Vertex[i].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Vertex[i].rhw = 0.0f;
		Vertex[i].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Vertex[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
}

//----�f�X�g���N�^--------
class_ObjectU::~class_ObjectU()
{

}

//----�`�揈��--------
void class_ObjectU::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}
void class_ObjectU::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//----���_�쐬--------
void class_ObjectU::MakeVertex(float sizeX, float sizeY, float posX, float posY)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
void class_ObjectU::MakeVertex(float sizeX, float sizeY)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	Vertex[0].rhw =
	Vertex[1].rhw =
	Vertex[2].rhw =
	Vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	Vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//----���_�ݒ�--------
void class_ObjectU::SetVertex(float sizeX, float sizeY, float posX, float posY)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = D3DXVECTOR3(-sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX + posX, -sizeY + posY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX + posX,  sizeY + posY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX + posX,  sizeY + posY, 0.0f);
}
void class_ObjectU::SetVertex(float sizeX, float sizeY)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = D3DXVECTOR3(-sizeX, -sizeY, 0.0f);
	Vertex[1].vtx = D3DXVECTOR3( sizeX, -sizeY, 0.0f);
	Vertex[2].vtx = D3DXVECTOR3(-sizeX,  sizeY, 0.0f);
	Vertex[3].vtx = D3DXVECTOR3( sizeX,  sizeY, 0.0f);
}
void class_ObjectU::SetVertex(D3DXCOLOR color)
{
	// ���ˌ��̐ݒ�
	Vertex[0].diffuse = color;
	Vertex[1].diffuse = color;
	Vertex[2].diffuse = color;
	Vertex[3].diffuse = color;
}

//----�ʒu�ݒ�(���ݒl���Z)--------
void class_ObjectU::SetPosition(float posX, float posY)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[1].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[2].vtx += D3DXVECTOR3(posX, posY, 0.0f);
	Vertex[3].vtx += D3DXVECTOR3(posX, posY, 0.0f);
}

//----�e�N�X�`�����W�ݒ�--------
void class_ObjectU::SetTexture(int num, int ix, int iy)
{
	int x = num % ix;
	int y = num / ix;
	float sizeX = 1.0f / ix;
	float sizeY = 1.0f / iy;
	Vertex[0].tex = D3DXVECTOR2((float)(x)* sizeX,         (float)(y)* sizeY);
	Vertex[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	Vertex[2].tex = D3DXVECTOR2((float)(x)* sizeX,         (float)(y)* sizeY + sizeY);
	Vertex[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//----�e�N�X�`�������N--------
LPDIRECT3DTEXTURE9 class_ObjectU::GetTextureAddress(LPDIRECT3DTEXTURE9 *texture)
{
	*texture = Texture;
	return Texture;
}

//----�o�b�t�@�n�J��--------
void class_ObjectU::ReleaseBuffer(void)
{
	if (Texture != NULL)
	{// �e�N�X�`���̊J��
		Texture->Release();
		Texture = NULL;
	}
}

//----�e�N�X�`����^����--------
void class_ObjectU::LoadTexture(const char *texture)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(GetDevice(), texture, &Texture);
}
void class_ObjectU::LoadTexture(LPDIRECT3DTEXTURE9 texture)
{
	// �e�N�X�`���̓ǂݍ���
	Texture = texture;
}

