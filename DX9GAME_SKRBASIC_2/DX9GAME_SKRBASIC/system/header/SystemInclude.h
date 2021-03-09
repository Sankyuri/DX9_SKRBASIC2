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




//��������������������������������  �\���̐錾  ��������������������������������

//����������������  ����  ����������������

//�|���S���̍��W
typedef struct tagVERTEX_2D VERTEX_2D;

//�摜�̍��W
typedef struct tagPOSITION_2D POSITION_2D;

//�摜�̍��W(3D)
typedef struct tagPOSITION_3D POSITION_3D;

//�摜�̃N���}�L�[���w�肷��
typedef struct tagALPHA_KEYCOLOR ALPHA_KEYCOLOR;

//�摜�̊�{�ݒ������\����
typedef struct tagTEXTURE_BASIC_SETTING TEXTURE_BASIC_SETTING;


//����������������  �w�i  ����������������

typedef struct tagBACKGROUND_SETTING BACKGROUND_SETTING;


//����������������  �L�����N�^�[�����G  ����������������

//�L�����N�^�[��ݒ肷��\����
typedef struct tagCHARACTER_TEXTURE_SETTING CHARACTER_TEXTURE_SETTING;

//�L�����N�^�[��ݒ肷��\��+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX CHARACTER_TEXTURE_SETTING_EX;


//����������������  �E�B���h�E  ����������������

//�e�L�X�g�E�B���h�E
typedef struct tagTEXTWINDOW_SETTING TEXTWINDOW_SETTING;











