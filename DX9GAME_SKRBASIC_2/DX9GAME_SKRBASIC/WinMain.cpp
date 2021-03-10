#include "system/header/SystemParam.h"
#include "system/header/Basic.h"
#include "system/header/Input.h"
#include "system/header/systemExtern.h"
#include "system/header/ImagePolygon.h"
#include "GameMain.h"

using namespace skrBasic;

bool g_skipProcesses = false; //�t�H�[�J�X�������ꍇ�ɏ��������Ȃ��p

static bool g_isGameEnd  = false; //�Q�[�����I�������邩
static bool g_isSlowMode = false; //�X���[���[�h��
static int  g_slowAmount = 3;     //�X���[���[�h�̑��x



static void drawStartupBG();

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, INT) {
	MSG msg; //���b�Z�[�W�n���h��


	// ���������[�N���o�̐ݒ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//msg���[���N���A
	ZeroMemory(&msg, sizeof(msg));

	//�m�x���Q�[���̃N���X��錾
	GameMain game;

	//�E�B���h�E�N���X�ݒ�
	WNDCLASSEX wc;
	InitWndClass(wc);

	//�������E�B���h�E�T�C�Y�ɂ��ăE�B���h�E�����
	const int wndWidth
		= SystemParam::getWindowWidth()  + (GetSystemMetrics(SM_CXFRAME) << 2);
	const int wndHeight
		= SystemParam::getWindowHeight() + (GetSystemMetrics(SM_CYFRAME) << 2)
		                                 +  GetSystemMetrics(SM_CYCAPTION);
	
	//��ʉ𑜓x�`�F�b�N
	if (GetSystemMetrics(SM_CXSCREEN) < wndWidth  ||
		GetSystemMetrics(SM_CYSCREEN) < wndHeight )
	{    //true : ��ʉ𑜓x������Ȃ��̂ŏI������
		Message(_T("��ʉ𑜓x������܂���B\n�Q�[�����I�����܂�"), _T("�������炸�c�c"));
		ShowCursor(true);
		Release();
		UnregisterClass(g_className, wc.hInstance);
		return -1;
	}

	//�E�B���h�E����
	game.createWindowSimple(SystemParam::getWindowTitle().c_str(), wndWidth, wndHeight, wc);

	//D3D�̏�����
	if (SUCCEEDED(game.initD3D(g_hWnd))) {
		//�E�B���h�E��\��
		ShowWindow(g_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(g_hWnd);

		//�N�����[�h�̔w�i�`��
		drawStartupBG();

		//���͏�����
		Input::init();

		//DSound������
		InitDSound(SystemParam::getDSPBufSamplingRate());

		//�����_�����O�X�e�[�g��������
		game.initRenderState();


		//�Q�[���{�̂̏�������
		if (FAILED(game.init())) {
			// �����Ɏ��s������I������
			game.gameEnd();
		}



		timeBeginPeriod(1);

		//���C��
		while (msg.message != WM_QUIT) {

			//CPU�ւ̃E�F�C�g
			Sleep(1);

			//�Q�[�����I�����邩
			if (g_isGameEnd) {
				break;
			}

			/*
			//�t���[�����[�g�Œ�
			if () {

			}
			*/


			//���[�v����
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//D3D�f�o�C�X�������[�X����Ă����ꍇ�̑΍�
			if (nullptr == g_pd3dDevice) {
				break;
			}

//			//�E�B���h�E����A�N�e�B�u�̎��̓X�L�b�v
//			if (skipProcesses) {
//				continue;
//			}

			// BGM�̃��[�v�`�F�b�N
			if (FAILED(game.bgmLoop())) {
				// �����Ɏ��s������I������
				game.gameEnd();
			}

			//�X���[���[�h�̎��͈��Ԋu�ŏ���
			if (g_isSlowMode) {
				if (0 != (game.getGCount() % g_slowAmount)) {
					game.addGCount();
					Sleep(g_slowAmount);
					continue;
				}
			}

			//�E�B���h�E��P�F�N���A
			g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);

			//�`��ƍX�V�̏���(BeginScene�����������ꍇ�Ɏ��s)
			if (SUCCEEDED(g_pd3dDevice->BeginScene())) {

//				//�f�o�C�X�̓��͏�Ԃ̎擾
//				Input::getInputDeviceState();
				//�E�B���h�E���A�N�e�B�u�̎��Ƀf�o�C�X�̓��͏�Ԃ̎擾
				if (not g_skipProcesses) {
					Input::getInputDeviceState();
				}

				//���C�����[�v
				if (FAILED(game.main())) {
					// �����Ɏ��s������I������
					game.gameEnd();
				}

				//�`����I��
				g_pd3dDevice->EndScene();

				//�O���[�o���J�E���g�����Z
				game.addGCount();

			} // if (SUCCEEDED(g_pd3dDevice->BeginScene()))

			//�o�b�t�@������(�`��)
			g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		} // while (msg.message != WM_QUIT)

	} // if (SUCCEEDED(game.InitD3D(hWnd)))

	//�I������
	timeEndPeriod(1);
	ShowCursor(true);
	Release();
	UnregisterClass(g_className, wc.hInstance);
	return 0;
}

//�N�����[�h���̔w�i�\��
static void drawStartupBG() {
	ImagePolygon bg;
	//�t�@�C�����݃`�F�b�N
	FILE *fp;
	fp = _tfopen(_T("resource/img/bg/bg_startupBG.png"), _T("r"));
	if (NULL == fp) { //���݂��Ȃ��ꍇ�͏������I��
		return;
	}
	fclose(fp);
	// �w�i�`��
	//�w�i�\������
	auto wndw = SystemParam::getWindowWidth();
	auto wndh = SystemParam::getWindowHeight();
	bg.load(_T("resource/img/bg/bg_startupBG.png"), wndw, wndh, D3DCOLOR(0));
	bg.setPos(wndw / 2.0f, wndh / 2.0f); // ��ʒ����Ɉړ�
	g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);
	if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		bg.draw();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//�Q�[���I��
void D3DBasicProcess::gameEnd() {
	g_isGameEnd = true;
}


//�X���[���[�h�؂�ւ�
void SlowMode(bool mode) {
	g_isSlowMode = mode;
}

//�X���[���[�h���x�ݒ�
void SlowModeSpeed(int amount) {
	g_slowAmount = 1 < amount ? amount : 2;
}



