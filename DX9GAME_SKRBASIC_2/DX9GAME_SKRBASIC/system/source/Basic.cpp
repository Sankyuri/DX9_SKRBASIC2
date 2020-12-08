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




void InitWndClass(WNDCLASSEX *a_wc) {
	a_wc->cbSize = sizeof(WNDCLASSEX);
	a_wc->style = CS_CLASSDC;
	a_wc->lpfnWndProc = (WNDPROC)MsgProc;
	a_wc->cbClsExtra = 0;
	a_wc->cbWndExtra = 0;
	a_wc->hInstance = GetModuleHandle(NULL);
	a_wc->hbrBackground = NULL;
	a_wc->lpszMenuName = NULL;
	a_wc->lpszClassName = g_ClassName;

	//カーソル設定
	#ifdef IDC_CURSOR1
		a_wc->hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1));
	#else
		a_wc->hCursor = NULL;
	#endif

	//アイコン設定
	#ifdef _DEBUG
		#ifdef IDI_ICON_D
			a_wc->hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_D));
		#else
			a_wc->hIcon   = NULL;
		#endif
		#ifdef IDI_ICON_SMALL_D
			a_wc->hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SMALL_D));
		#else
			a_wc->hIconSm = NULL;
		#endif
	#else
		#ifdef IDI_ICON
			a_wc->hIcon   = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
		#else
			a_wc->hIcon   = NULL;
		#endif
		#ifdef IDI_ICON_SMALL
			a_wc->hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SMALL));
		#else
			a_wc->hIconSm = NULL;
		#endif
	#endif //大分汚いがこれで勘弁しておくれ……

	RegisterClassEx(a_wc);
}


LRESULT WINAPI MsgProc(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_msg)
	{
		//ウィンドウサイズ変更
	case WM_SIZE:
		float width, height;
		width = (float)(a_lParam & 0xFFFF);
		height = (float)((a_lParam >> 16) & 0xFFFF);
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
		SetFocus(a_hWnd);
		skipProcesses = false;
		break;
	}
	return DefWindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
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
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, g_aspect, 1.0f, 10.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}








void Message(LPCTSTR text, LPCTSTR title) {
	MessageBox(hWnd, text, title, MB_OK);
}











