#pragma once

//DInputのバージョン不明の警告を出さなくする奴
#define DIRECTINPUT_VERSION 0x0800

//ライブラリ
#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")


//ヘッダ
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#include <d3dx9.h>
#include <dxerr.h>
#include <dinput.h>
#include <dsound.h>


//なんかバージョンアップで dxerr.hのDXTRACE_ERR() を使用するとエラーが起こるので次の文が必要とのこと(Slnの設定でも可)
#pragma comment(lib, "legacy_stdio_definitions.lib" )






