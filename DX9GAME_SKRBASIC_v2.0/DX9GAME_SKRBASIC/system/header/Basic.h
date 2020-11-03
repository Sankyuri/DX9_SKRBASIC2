#pragma once
#include "SystemInclude.h"


//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  関数クラス  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

//＊＊＊＊  ウィンドウに対する基本処理  ＊＊＊＊

//メッセージプロシージャ
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ウィンドウクラス設定
void           InitWndClass(WNDCLASSEX *wc);

//アスペクト比設定
void           SetupMatrices();

//解放処理
HRESULT        Release();

//DSound 初期化
void           InitDSound(DWORD samplingRate);




//＊＊＊＊  ウィンドウ情報関数  ＊＊＊＊

//スローモード切り替え<使用不可>
//@deprecated
void  SlowMode(bool mode);

//スローモード速度設定<使用不可>
//@deprecated
void  SlowModeSpeed(int amount);




//＊＊＊＊  その他便利関数/関数マクロ  ＊＊＊＊

//超簡易メッセージボックス
void  Message(LPCTSTR text, LPCTSTR title);

#define SafeDelete(p)      if((p)) { delete   (p);   (p) = nullptr; };
#define SafeDeleteArray(p) if((p)) { delete[] (p);   (p) = nullptr; };
#define SafeRelease(p)     if((p)) { (p)->Release(); (p) = nullptr; };



