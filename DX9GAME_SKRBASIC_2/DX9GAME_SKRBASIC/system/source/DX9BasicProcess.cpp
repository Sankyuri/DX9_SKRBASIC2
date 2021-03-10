//#include "..\header\SKRGameCommon.h"
//#include "..\header\systemExtern.h"
#include "..\header\Basic.h"
#include "..\header\SystemParam.h"
#include "..\header\D3DBasicProcess.h"
#include "..\header\systemExtern.h"

using namespace skrBasic;

//マクロ
#define WINDOW_SETTING (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX) //ウィンドウの設定用マクロ


//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  関数  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

HRESULT D3DBasicProcess::initD3D(HWND a_hWnd) {
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == g_pD3D) {
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth  = SystemParam::getWindowWidth();
	d3dpp.BackBufferHeight = SystemParam::getWindowHeight();
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount  = 3;

	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, a_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice))) {
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, a_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pd3dDevice))) {
			Message(_T("HALモードが使えないようです…"), _T("Error"));
			if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, a_hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &g_pd3dDevice)))) {
				if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, a_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &g_pd3dDevice)))) {
					Message(_T("デバイスの作成に失敗しました"), _T("Error"));
					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}

void D3DBasicProcess::createWindowSimple(LPCTSTR a_wndName, int a_wndW, int a_wndH, WNDCLASSEX &a_wc) {
	D3DDISPLAYMODE disppos;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disppos);
	g_hWnd = CreateWindow(g_className, a_wndName, WINDOW_SETTING,
		                CW_USEDEFAULT, CW_USEDEFAULT,
		                a_wndW, a_wndH, NULL, NULL, a_wc.hInstance, NULL);
}

void D3DBasicProcess::initRenderState() {
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリング無効化(2Dゲームなので)
	getWindowRenderState(); //ウィンドウのターゲット情報取得
	enableAlphaBlend(); //アルファブレンド有効化
}

void D3DBasicProcess::getWindowRenderState() {
	g_pd3dDevice->GetViewport(&m_wndVp);
	g_pd3dDevice->GetRenderTarget(0, &m_wndRt);
	g_pd3dDevice->GetDepthStencilSurface(&m_wndZb);
}

void D3DBasicProcess::enableAlphaBlend() {
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP  , D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE  );
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE  );
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE                );
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND        , D3DBLEND_SRCALPHA   );
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND       , D3DBLEND_INVSRCALPHA);
}

HRESULT D3DBasicProcess::D3DBPSetRenderTarget() {
	g_pd3dDevice->SetViewport(&m_wndVp);
	g_pd3dDevice->SetRenderTarget(0, m_wndRt);
	g_pd3dDevice->SetDepthStencilSurface(m_wndZb);
	return S_OK;
}

HRESULT D3DBasicProcess::resetRenderTarget() {
	g_pd3dDevice->SetViewport(&m_wndVp);
	g_pd3dDevice->SetRenderTarget(0, m_wndRt);
	g_pd3dDevice->SetDepthStencilSurface(m_wndZb);
	return S_OK;
}

ULONGLONG D3DBasicProcess::getGCount() {
	return m_gCount;
}

void D3DBasicProcess::addGCount() {
	++m_gCount;
}




#undef WINDOW_SETTING



