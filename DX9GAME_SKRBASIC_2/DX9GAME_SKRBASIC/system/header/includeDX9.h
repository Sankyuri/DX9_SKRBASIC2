#pragma once

//DInput�̃o�[�W�����s���̌x�����o���Ȃ�����z
#define DIRECTINPUT_VERSION 0x0800

//���C�u����
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


//�w�b�_
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#include <d3dx9.h>
#include <dxerr.h>
#include <dinput.h>
#include <dsound.h>


//�Ȃ񂩃o�[�W�����A�b�v�� dxerr.h��DXTRACE_ERR() ���g�p����ƃG���[���N����̂Ŏ��̕����K�v�Ƃ̂���(Sln�̐ݒ�ł���)
#pragma comment(lib, "legacy_stdio_definitions.lib" )






