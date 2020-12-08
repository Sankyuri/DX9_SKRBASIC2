#include "system/header/SystemParam.h"
#include "system/header/Basic.h"
#include "system/header/Input.h"
#include "system/header/systemExtern.h"
#include "system/header/ImagePolygon.h"
#include "GameMain.h"

using namespace skrBasic;

bool skipProcesses = false; //�t�H�[�J�X�������ꍇ�ɏ��������Ȃ��p
bool isGameEnd     = false; //�Q�[�����I�������邩
bool isSlowMode    = false; //�X���[���[�h��
int  slowAmount    = 3;     //�X���[���[�h�̑��x
MSG  msg; //���b�Z�[�W�n���h��



static void drawStartupBG();

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, INT) {

	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//msg���[���N���A
	ZeroMemory(&msg, sizeof(msg));

	//�m�x���Q�[���̃N���X��錾
	GameMain game;

	//�E�B���h�E�N���X�ݒ�
	WNDCLASSEX wc;
	InitWndClass(&wc);

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
		UnregisterClass(g_ClassName, wc.hInstance);
		return -1;
	}

	//�E�B���h�E����
	game.createWindowSimple(SystemParam::getWindowTitle().c_str(), wndWidth, wndHeight, &wc);

	//D3D�̏�����
	if (SUCCEEDED(game.initD3D(hWnd))) {
		//�E�B���h�E��\��
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		//�N�����[�h�̔w�i�`��
		drawStartupBG();

		//���͏�����
		Input::init();

		//DSound������
		InitDSound(SystemParam::getDSPBufSamplingRate());

		//�����_�����O�X�e�[�g��������
		game.initRenderState();


		//�Q�[���{�̂̏�������
		game.init();




		//���C��
		while (msg.message != WM_QUIT) {

			//CPU�ւ̃E�F�C�g
			Sleep(1);

			/*
			//�t���[�����[�g�Œ�
			if () {

			}
			*/

			//�Q�[�����I�����邩
			if (isGameEnd) {
				break;
			}


			//���[�v����
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//D3D�f�o�C�X�������[�X����Ă����ꍇ�̑΍�
			if (g_pd3dDevice == NULL) {
				break;
			}

//			//�E�B���h�E����A�N�e�B�u�̎��̓X�L�b�v
//			if (skipProcesses) {
//				continue;
//			}

			//�X���[���[�h�̎��͈��Ԋu�ŏ���
			if (true == isSlowMode) {
				if (0 != (game.getGCount() % slowAmount)) {
					game.addGCount();
					Sleep(slowAmount);
					continue;
				}
			}

			//�E�B���h�E��P�F�N���A
			g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);

			//�`��ƍX�V�̏���(BeginScene�����������ꍇ�Ɏ��s)
			if (SUCCEEDED(g_pd3dDevice->BeginScene())) {

//				//�f�o�C�X�̓��͏�Ԃ̎擾
//				Input::getInputDeviceState();
				//�E�B���h�E���A�N�e�B�u�̎��Ƀf�o�C�X�̓��͏�Ԃ̎擾
				if (false == skipProcesses) {
					Input::getInputDeviceState();
				}

				//���C�����[�v
				game.main();

				//�`����I��
				g_pd3dDevice->EndScene();

				//�O���[�o���J�E���g�����Z
				game.addGCount();

			}

			g_pd3dDevice->Present(NULL, NULL, NULL, NULL); //�o�b�t�@������(�`��)

		} // while (msg.message != WM_QUIT)

	} // if (SUCCEEDED(game.InitD3D(hWnd)))

	//�I������
	ShowCursor(true);
	Release();
	UnregisterClass(g_ClassName, wc.hInstance);
	return 0;
}

//�N�����[�h���̔w�i�\��
static void drawStartupBG() {
	ImagePolygon bg;
	FILE *fp; //�t�@�C�����݃`�F�b�N�p
	fp = _tfopen(_T("resource/img/bg/bg_startupBG.png"), _T("r"));
	if (NULL == fp) { //���݂��Ȃ��ꍇ�͏������I��
		return;
	}
	fclose(fp);
	bg.load(_T("resource/img/bg/bg_startupBG.png"),
			SystemParam::getWindowWidth(), SystemParam::getWindowHeight(), NULL);
	bg.setPos(SystemParam::getWindowWidth() / 2, SystemParam::getWindowHeight() / 2);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);
	if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		bg.draw();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//�Q�[���I��
void GameMain::gameEnd() {
	isGameEnd = true;
}


//�X���[���[�h�؂�ւ�
void SlowMode(bool mode) {
	isSlowMode = mode;
}

//�X���[���[�h���x�ݒ�
void SlowModeSpeed(int amount) {
	slowAmount = 1 < amount ? amount : 2;
}



