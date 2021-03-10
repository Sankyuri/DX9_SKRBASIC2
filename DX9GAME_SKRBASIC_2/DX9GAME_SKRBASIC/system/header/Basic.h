#pragma once
#include "SystemInclude.h"


//��������������������������������  �֐��N���X  ��������������������������������

//��������  �E�B���h�E�ɑ΂����{����  ��������

//���b�Z�[�W�v���V�[�W��
LRESULT WINAPI MsgProc(HWND a_hWnd, UINT a_msg, WPARAM a_wParam, LPARAM a_lParam);

//�E�B���h�E�N���X�ݒ�
void           InitWndClass(WNDCLASSEX &a_wc);

//�A�X�y�N�g��ݒ�
void           SetupMatrices();

//�������
HRESULT        Release();

//DSound ������
void           InitDSound(DWORD a_samplingRate);




//��������  �E�B���h�E���֐�  ��������

//�X���[���[�h�؂�ւ�<�g�p�s��>
//@deprecated
void  SlowMode(bool a_mode);

//�X���[���[�h���x�ݒ�<�g�p�s��>
//@deprecated
void  SlowModeSpeed(int a_amount);




//��������  ���̑��֗��֐�/�֐��}�N��  ��������

//���ȈՃ��b�Z�[�W�{�b�N�X
void  Message(LPCTSTR a_text, LPCTSTR a_title);

#define SafeDelete(a_p)      if((a_p)) { delete   (a_p);   (a_p) = nullptr; };
#define SafeDeleteArray(a_p) if((a_p)) { delete[] (a_p);   (a_p) = nullptr; };
#define SafeRelease(a_p)     if((a_p)) { (a_p)->Release(); (a_p) = nullptr; };



