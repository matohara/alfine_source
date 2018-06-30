//=============================================================================
//
// ���C������ [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "light.h"
#include "Camera.h"
#include "sound.h"

#include "source/scene/fade.h"
#include "source/scene/title.h"
#include "source/scene/StageSelect.h"
#include "source/scene/result.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"HPTApplication"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�t���ϑ����앨"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)

HWND hWnd;

int			g_nCountFPS;			// FPS�\�L�p�J�E���^
bool		g_bDispDebug = false;	// �f�o�b�O�\��ON/OFF
GAMESCENE	g_GameScene = SCENE_MAX;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;	// �O����s����
	DWORD dwFPSLastTime;	// �O��FPS�X�V�����ێ�
	DWORD dwCurrentTime;	// �������ێ�
	DWORD dwFrameCount;		// FPS�J�E���^
	DWORD dwHighTimer;		// ����1F�^�C�}�[
//	DWORD dwPrecisionTime;	// ����1S�^�C�}�[(����ł���邱�Ƃ���������g�p����)

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	MSG msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);
	dwExecLastTime =
//	dwPrecisionTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();				// �������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���Ƃɕ\�L�pFPS�J�E���^���X�V
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// �O���FPS�\�L�p��������������
				dwFrameCount = 0;	// �ăJ�E���g�̂��߂Ƀ��Z�b�g
			}

			// 60FPS�̐�����(�덷(+-)2)

			dwHighTimer = (dwFrameCount % 3) == 0 ? 16 : 17;
#ifdef _DEBUG
			if (GetKeyboardPress(DIK_2))
			{
				dwHighTimer = 8;
			}
			if (GetKeyboardPress(DIK_4))
			{
				dwHighTimer = 4;
			}
#endif // _DEBUG

			DWORD dwloop = (dwCurrentTime - dwExecLastTime) / dwHighTimer;
			if (dwloop > 0)
			{
				PrintDebugProcess("FPS:%d\n", g_nCountFPS);
				dwExecLastTime = dwCurrentTime;

				for (UINT i = 0; (i < dwloop) & (i < 60); i++)
				{
					// �X�V����
					Update();

					// �`�揈��
					Draw();

					dwFrameCount++;
				}
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	timeEndPeriod(1);	// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		//switch(wParam)
		//{
		//case VK_ESCAPE:
		//	DestroyWindow(hWnd);
		//	break;
		//}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W���Z��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	// ���͂̏�����
	InitInput(hInstance, hWnd);

	// �f�o�b�O�\���̏�����
	InitDebugProcess();

	// �t�F�[�h
	CSFade::MakeVertex();

	// �T�E���h������
	InitSound(hWnd);

	// �^�C�g���V�[���ɃZ�b�g
	SetGameScene(SCENE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	SetGameScene(SCENE_END);

	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// ���͂̏I������
	UninitInput();

	// �f�o�b�O�\�������̏I������
	UninitDebugProcess();

	// �T�E���h�I������

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	if(GetKeyboardTrigger(DIK_F3))
	{// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false: true;
	}

	// ���͂̍X�V����
	UpdateInput();

	switch (g_GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̍X�V����
		UpdateTitle();
		break;
	case SCENE_STAGESELECT:
		// �X�e�[�W�I���V�[���̍X�V����
		UpdateStageSelect();
		if (GetKeyboardTrigger(DIK_ESCAPE))
		{
			CSFade::SetFade(SCENE_TITLE);
		}
		break;
	case SCENE_TUTORIAL:
		// �`���[�g���A���V�[���̍X�V����

		break;
	case SCENE_GAME:
		// �Q�[���V�[���̍X�V
		UpdateGame();
		if (GetKeyboardTrigger(DIK_ESCAPE))
		{

		}
		break;
	case SCENE_RESULT:
		// ���U���g�V�[���̍X�V����
		UpdateResult();
		break;
	case SCENE_PAUSE:
		// �|�[�Y�V�[���̍X�V����

		break;
		break;
	default:
		break;
	}

	// �t�F�[�h�����̍X�V
	CSFade::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_GameScene)
		{
		case SCENE_TITLE:
			// �^�C�g���V�[���̕`�揈��
			DrawTitle();
			break;
		case SCENE_STAGESELECT:
			// �X�e�[�W�I���V�[���̕`�揈��
			DrawStageSelect();
			break;
		case SCENE_TUTORIAL:
			// �`���[�g���A���V�[���̕`�揈��

			break;
		case SCENE_GAME:
			// �Q�[���V�[���̕`�揈��
			DrawGame();
			break;
		case SCENE_RESULT:
			// ���U���g�̕`�揈��
			DrawGame();// �Q�[���V�[���̕`�揈��
			DrawResult();
			break;
		case SCENE_PAUSE:
			// �|�[�Y�V�[���̕`�揈��

			break;
		default:
			break;
		}

		// �t�F�[�h�`��
		CSFade::Draw();

		// �f�o�b�O�\���̕`�揈��
		if (g_bDispDebug)
		{
			DrawDebugProcess();
		}

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// �Q�[���V�[���̍X�V�E�擾
//=============================================================================
GAMESCENE SetGameScene(GAMESCENE scene)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if ((g_GameScene == scene) || (scene == SCENE_MAX))
	{
		return g_GameScene;
	}

	/* ���݂̃V�[���̂��Еt�� */
	switch (g_GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏I������
		UninitTitle();
		break;
	case SCENE_STAGESELECT:
		// �X�e�[�W�I���V�[���̏I������
		UninitStageSelect();
		break;
	case SCENE_TUTORIAL:
		// �`���[�g���A���V�[���̏I������

		// �|�[�Y�V�[���̏I������

		// �J�b�g�C���V�[���̏I������

		break;
	case SCENE_GAME:
		// �Q�[���V�[���̏I������ ���U���g�ɓ���
		//UninitGame();

		// �|�[�Y�V�[���̏I������

		// �J�b�g�C���V�[���̏I������

		break;
	case SCENE_RESULT:
		// ���U���g�V�[���̏I������
		UninitResult();

		// �Q�[���V�[���̏I������
		UninitGame();

		break;
	case SCENE_PAUSE:
		break;
	default:
		break;
	}

	/* ���̃V�[���̏��� */
	switch (scene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏�����
		InitTitle();

		g_GameScene = SCENE_TITLE;
		break;
	case SCENE_STAGESELECT:
		// �X�e�[�W�I���V�[���̏�����
		InitStageSelect();

		g_GameScene = SCENE_STAGESELECT;
		break;
	case SCENE_TUTORIAL:
		// �`���[�g���A���V�[���̏�����

		// �|�[�Y�V�[���̏�����

		g_GameScene = SCENE_TUTORIAL;
		break;
	case SCENE_GAME:
		// �Q�[���V�[���̏�����
		InitGame();

		// �|�[�Y�V�[���̏�����

		g_GameScene = SCENE_GAME;
		break;
	case SCENE_RESULT:
		// ���U���g�V�[���̏�����
		InitResult();

		g_GameScene = SCENE_RESULT;
		break;
	case SCENE_PAUSE:
		g_GameScene = SCENE_PAUSE;
		break;
	default:
		return g_GameScene;
		break;
	}

	g_GameScene = scene;

	return g_GameScene;
}

//=============================================================================
// window�n���h���擾
//=============================================================================
HWND GethWnd(void)
{
	return hWnd;
}
