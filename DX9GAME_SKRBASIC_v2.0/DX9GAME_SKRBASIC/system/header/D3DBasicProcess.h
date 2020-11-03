#pragma once
#include "SystemInclude.h"

namespace skrBasic{

	//
	//  ゲーム基本処理系統
	//
	class D3DBasicProcess {
	public:
		//レンダリングターゲットをZバッファに戻す
		//@return 
		HRESULT resetRenderTarget();

		//ゲームの起動からの経過時間(count)を取得
		ULONGLONG getGCount();



		//Direct3Dの初期化
		HRESULT initD3D(HWND hWnd);

		//レンダリングステートを初期化
		void    initRenderState();

		//簡易ウィンドウ生成
		void    createWindowSimple(LPCTSTR wndName, int wndW, int wndH, WNDCLASSEX *wc);

		//gCount を 1 加算
		void addGCount();


	private:
		ULONGLONG gCount = 0;    //グローバルカウンタ

		D3DVIEWPORT9        vp_wnd;         //ウィンドウのビューポート
		LPDIRECT3DSURFACE9  rt_wnd, zb_wnd; //ウィンドウのレンダリングターゲット情報 / ウィンドウのZバッファ情報

		void    enableAlphaBlend();     //アルファブレンドを有効にする
		void    getWindowRenderState(); //ウィンドウのターゲット情報を取得

		HRESULT D3DBP_SetRenderTarget();   //レンダリングターゲットを変更

	};

};



