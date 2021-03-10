#include "system/header/SystemParam.h"
#include "system/header/Basic.h"
#include "system/header/Input.h"
#include "system/header/systemExtern.h"
#include "system/header/ImagePolygon.h"
#include "GameMain.h"

using namespace skrBasic;

bool g_skipProcesses = false; //フォーカスが無い場合に処理をしない用

static bool g_isGameEnd  = false; //ゲームを終了させるか
static bool g_isSlowMode = false; //スローモードか
static int  g_slowAmount = 3;     //スローモードの速度



static void drawStartupBG();

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, INT) {
	MSG msg; //メッセージハンドル


	// メモリリーク検出の設定
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//msgをゼロクリア
	ZeroMemory(&msg, sizeof(msg));

	//ノベルゲームのクラスを宣言
	GameMain game;

	//ウィンドウクラス設定
	WNDCLASSEX wc;
	InitWndClass(wc);

	//正しいウィンドウサイズにしてウィンドウを作る
	const int wndWidth
		= SystemParam::getWindowWidth()  + (GetSystemMetrics(SM_CXFRAME) << 2);
	const int wndHeight
		= SystemParam::getWindowHeight() + (GetSystemMetrics(SM_CYFRAME) << 2)
		                                 +  GetSystemMetrics(SM_CYCAPTION);
	
	//画面解像度チェック
	if (GetSystemMetrics(SM_CXSCREEN) < wndWidth  ||
		GetSystemMetrics(SM_CYSCREEN) < wndHeight )
	{    //true : 画面解像度が足りないので終了する
		Message(_T("画面解像度が足りません。\nゲームを終了します"), _T("悪しからず……"));
		ShowCursor(true);
		Release();
		UnregisterClass(g_className, wc.hInstance);
		return -1;
	}

	//ウィンドウ生成
	game.createWindowSimple(SystemParam::getWindowTitle().c_str(), wndWidth, wndHeight, wc);

	//D3Dの初期化
	if (SUCCEEDED(game.initD3D(g_hWnd))) {
		//ウィンドウを表示
		ShowWindow(g_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(g_hWnd);

		//起動ロードの背景描画
		drawStartupBG();

		//入力初期化
		Input::init();

		//DSound初期化
		InitDSound(SystemParam::getDSPBufSamplingRate());

		//レンダリングステートを初期化
		game.initRenderState();


		//ゲーム本体の初期処理
		if (FAILED(game.init())) {
			// 処理に失敗したら終了する
			game.gameEnd();
		}



		timeBeginPeriod(1);

		//メイン
		while (msg.message != WM_QUIT) {

			//CPUへのウェイト
			Sleep(1);

			//ゲームを終了するか
			if (g_isGameEnd) {
				break;
			}

			/*
			//フレームレート固定
			if () {

			}
			*/


			//ループ処理
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//D3Dデバイスがリリースされていた場合の対策
			if (nullptr == g_pd3dDevice) {
				break;
			}

//			//ウィンドウが非アクティブの時はスキップ
//			if (skipProcesses) {
//				continue;
//			}

			// BGMのループチェック
			if (FAILED(game.bgmLoop())) {
				// 処理に失敗したら終了する
				game.gameEnd();
			}

			//スローモードの時は一定間隔で処理
			if (g_isSlowMode) {
				if (0 != (game.getGCount() % g_slowAmount)) {
					game.addGCount();
					Sleep(g_slowAmount);
					continue;
				}
			}

			//ウィンドウを単色クリア
			g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);

			//描画と更新の処理(BeginSceneが成功した場合に実行)
			if (SUCCEEDED(g_pd3dDevice->BeginScene())) {

//				//デバイスの入力状態の取得
//				Input::getInputDeviceState();
				//ウィンドウがアクティブの時にデバイスの入力状態の取得
				if (not g_skipProcesses) {
					Input::getInputDeviceState();
				}

				//メインループ
				if (FAILED(game.main())) {
					// 処理に失敗したら終了する
					game.gameEnd();
				}

				//描画を終了
				g_pd3dDevice->EndScene();

				//グローバルカウントを加算
				game.addGCount();

			} // if (SUCCEEDED(g_pd3dDevice->BeginScene()))

			//バッファを交換(描画)
			g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		} // while (msg.message != WM_QUIT)

	} // if (SUCCEEDED(game.InitD3D(hWnd)))

	//終了処理
	timeEndPeriod(1);
	ShowCursor(true);
	Release();
	UnregisterClass(g_className, wc.hInstance);
	return 0;
}

//起動ロード時の背景表示
static void drawStartupBG() {
	ImagePolygon bg;
	//ファイル存在チェック
	FILE *fp;
	fp = _tfopen(_T("resource/img/bg/bg_startupBG.png"), _T("r"));
	if (NULL == fp) { //存在しない場合は処理を終了
		return;
	}
	fclose(fp);
	// 背景描画
	//背景表示処理
	auto wndw = SystemParam::getWindowWidth();
	auto wndh = SystemParam::getWindowHeight();
	bg.load(_T("resource/img/bg/bg_startupBG.png"), wndw, wndh, D3DCOLOR(0));
	bg.setPos(wndw / 2.0f, wndh / 2.0f); // 画面中央に移動
	g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET, SystemParam::getClearColor(), 1.0f, 0);
	if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		bg.draw();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//ゲーム終了
void D3DBasicProcess::gameEnd() {
	g_isGameEnd = true;
}


//スローモード切り替え
void SlowMode(bool mode) {
	g_isSlowMode = mode;
}

//スローモード速度設定
void SlowModeSpeed(int amount) {
	g_slowAmount = 1 < amount ? amount : 2;
}



