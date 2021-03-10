#pragma once
#include "SystemInclude.h"


//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  関数クラス  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

//＊＊＊＊  ウィンドウに対する基本処理  ＊＊＊＊

//メッセージプロシージャ
LRESULT WINAPI MsgProc(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);

//ウィンドウクラス設定
void           InitWndClass(WNDCLASSEX &a_wc);

//アスペクト比設定
void           SetupMatrices();

//解放処理
HRESULT        Release();

//DSound 初期化
void           InitDSound(DWORD a_samplingRate);




//＊＊＊＊  ウィンドウ情報関数  ＊＊＊＊

//スローモード切り替え<使用不可>
//@deprecated
void  SlowMode(bool a_mode);

//スローモード速度設定<使用不可>
//@deprecated
void  SlowModeSpeed(int a_amount);




//＊＊＊＊  その他便利関数/関数マクロ  ＊＊＊＊

//超簡易メッセージボックス
void  Message(LPCTSTR a_text, LPCTSTR a_title);

#define SafeDelete(a_p)      if((a_p)) { delete   (a_p);   (a_p) = nullptr; };
#define SafeDeleteArray(a_p) if((a_p)) { delete[] (a_p);   (a_p) = nullptr; };
#define SafeRelease(a_p)     if((a_p)) { (a_p)->Release(); (a_p) = nullptr; };



