#include "..\header\includeDX9.h"

//DirectX
LPDIRECT3D9		     g_pD3D       = NULL;
LPDIRECT3DDEVICE9    g_pd3dDevice = NULL;
HWND                 hWnd;

//DirectInput
LPDIRECTINPUT8       g_pDInput;
LPDIRECTINPUT8       g_pDInputJ;
LPDIRECTINPUT8       g_pDInputM;
LPDIRECTINPUTDEVICE8 g_lpKeyboard = NULL;
LPDIRECTINPUTDEVICE8 g_lpJoypad   = NULL;
LPDIRECTINPUTDEVICE8 g_lpMouse    = NULL;
DIDEVCAPS            g_diJoyCaps;

//DirectSound
LPDIRECTSOUND8       g_pDSound;
LPDIRECTSOUNDBUFFER  g_pDSBuf;

//‚»‚Ì‘¼











