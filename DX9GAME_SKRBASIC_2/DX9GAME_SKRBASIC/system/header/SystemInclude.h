#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <Windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")



#include "includeDX9.h"
#include "struct.h"


#pragma warning(disable:4244)
#pragma warning(disable:4996)




//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  構造体宣言  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

//＊＊＊＊＊＊＊＊  共通  ＊＊＊＊＊＊＊＊

//ポリゴンの座標
typedef struct tagVERTEX_2D VERTEX_2D;

//画像の座標
typedef struct tagPOSITION_2D POSITION_2D;

//画像の座標(3D)
typedef struct tagPOSITION_3D POSITION_3D;

//画像のクロマキーを指定する
typedef struct tagALPHA_KEYCOLOR ALPHA_KEYCOLOR;

//画像の基本設定をする構造体
typedef struct tagTEXTURE_BASIC_SETTING TEXTURE_BASIC_SETTING;


//＊＊＊＊＊＊＊＊  背景  ＊＊＊＊＊＊＊＊

typedef struct tagBACKGROUND_SETTING BACKGROUND_SETTING;


//＊＊＊＊＊＊＊＊  キャラクター立ち絵  ＊＊＊＊＊＊＊＊

//キャラクターを設定する構造体
typedef struct tagCHARACTER_TEXTURE_SETTING CHARACTER_TEXTURE_SETTING;

//キャラクターを設定する構造+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX CHARACTER_TEXTURE_SETTING_EX;


//＊＊＊＊＊＊＊＊  ウィンドウ  ＊＊＊＊＊＊＊＊

//テキストウィンドウ
typedef struct tagTEXTWINDOW_SETTING TEXTWINDOW_SETTING;











