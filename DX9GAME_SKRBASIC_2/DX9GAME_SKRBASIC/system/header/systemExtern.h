#pragma once
#include "SystemInclude.h"


//DirectX
extern LPDIRECT3D9		    g_pD3D;
extern LPDIRECT3DDEVICE9    g_pd3dDevice;
extern HWND                 hWnd;
extern const TCHAR          *g_ClassName;

//DirectInput
extern LPDIRECTINPUT8       g_pDInput;
extern LPDIRECTINPUT8       g_pDInputJ;
extern LPDIRECTINPUT8       g_pDInputM;
extern LPDIRECTINPUTDEVICE8 g_lpKeyboard;
extern LPDIRECTINPUTDEVICE8 g_lpJoypad;
extern LPDIRECTINPUTDEVICE8 g_lpMouse;
extern DIDEVCAPS            g_diJoyCaps;

//DirectSound
extern LPDIRECTSOUND8       g_pDSound;
extern LPDIRECTSOUNDBUFFER  g_pDSBuf;



