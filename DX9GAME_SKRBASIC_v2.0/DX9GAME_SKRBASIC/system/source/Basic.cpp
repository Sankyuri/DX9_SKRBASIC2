#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#if __has_include("..\..\icon\header\icon.h") 
	#include "..\..\icon\header\icon.h"
#endif
#if __has_include("..\..\cursor\cursor.h") 
	#include "..\..\cursor\cursor.h"
#endif



float        g_aspect = 1; //アス比設定用変数
const TCHAR *g_ClassName = _T("SKR_GAME"); //ウィンドウクラス名

extern bool  skipProcesses; //WinMain.cpp の処理スキップ用




void InitWndClass(WNDCLASSEX *wc) {
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->style = CS_CLASSDC;
	wc->lpfnWndProc = (WNDPROC)MsgProc;
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->hInstance = GetModuleHandle(NULL);
	wc->hbrBackground = NULL;
	wc->lpszMenuName = NULL;
	wc->lpszClassName = g_ClassName;

	//カーソル設定
	#ifdef IDC_CURSOR1
		wc->hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1));
	#else
		wc->hCursor = NULL;
	#endif

	//アイコン設定
	#ifdef _DEBUG
		#ifdef IDI_ICON_D
			wc->hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_D));
		#else
			wc->hIcon   = NULL;
		#endif
		#ifdef IDI_ICON_SMALL_D
			wc->hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SMALL_D));
		#else
			wc->hIconSm = NULL;
		#endif
	#else
		#ifdef IDI_ICON
			wc->hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
		#else
			wc->hIcon   = NULL;
		#endif
		#ifdef IDI_ICON_SMALL
			wc->hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SMALL));
		#else
			wc->hIconSm = NULL;
		#endif
	#endif //大分汚いがこれで勘弁しておくれ……

	RegisterClassEx(wc);
}


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//ウィンドウサイズ変更
	case WM_SIZE:
		float width, height;
		width = (float)(lParam & 0xFFFF);
		height = (float)((lParam >> 16) & 0xFFFF);
		g_aspect = width / height;
		SetupMatrices();
		break;

		//ゲームを終了
	case WM_DESTROY:
		Release();
		PostQuitMessage(0);
		return 0;


	case WM_KILLFOCUS:
		skipProcesses = true;
		break;

	case WM_SETFOCUS:
		SetFocus(hWnd);
		skipProcesses = false;
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}




HRESULT Release()
{
	SafeRelease(g_pd3dDevice);
	SafeRelease(g_pD3D);

	SafeRelease(g_pDInput);
	SafeRelease(g_pDInputJ);
	SafeRelease(g_pDInputM);
	if (g_lpKeyboard != NULL) {
		g_lpKeyboard->Unacquire();
		SafeRelease(g_lpKeyboard);
	}
	if (g_lpJoypad != NULL) {
		g_lpJoypad->Unacquire();
		SafeRelease(g_lpJoypad);
	}
	if (g_lpMouse != NULL) {
		g_lpMouse->Unacquire();
		SafeRelease(g_lpMouse);
	}

	SafeRelease(g_pDSBuf);
	SafeRelease(g_pDSound);
	return S_OK;
}


VOID SetupMatrices()
{
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, g_aspect, 1.0f, 10.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}








void Message(LPCTSTR text, LPCTSTR title) {
	MessageBox(hWnd, text, title, MB_OK);
}











