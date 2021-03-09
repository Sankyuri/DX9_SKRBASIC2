#include "..\header\includeDX9.h"

//DirectX
LPDIRECT3D9		     g_pD3D       = nullptr;
LPDIRECT3DDEVICE9    g_pd3dDevice = nullptr;
HWND                 g_hWnd       = nullptr;

//DirectInput
LPDIRECTINPUT8       g_pDInput    = nullptr;
LPDIRECTINPUT8       g_pDInputJ   = nullptr;
LPDIRECTINPUT8       g_pDInputM   = nullptr;
LPDIRECTINPUTDEVICE8 g_lpKeyboard = nullptr;
LPDIRECTINPUTDEVICE8 g_lpJoypad   = nullptr;
LPDIRECTINPUTDEVICE8 g_lpMouse    = nullptr;
DIDEVCAPS            g_diJoyCaps;

//DirectSound
LPDIRECTSOUND8       g_pDSound    = nullptr;
LPDIRECTSOUNDBUFFER  g_pDSBuf     = nullptr;

//‚»‚Ì‘¼











