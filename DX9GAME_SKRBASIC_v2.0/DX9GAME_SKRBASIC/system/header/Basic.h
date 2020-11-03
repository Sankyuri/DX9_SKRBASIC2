#pragma once
#include "SystemInclude.h"


//��������������������������������  �֐��N���X  ��������������������������������

//��������  �E�B���h�E�ɑ΂����{����  ��������

//���b�Z�[�W�v���V�[�W��
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�E�B���h�E�N���X�ݒ�
void           InitWndClass(WNDCLASSEX *wc);

//�A�X�y�N�g��ݒ�
void           SetupMatrices();

//�������
HRESULT        Release();

//DSound ������
void           InitDSound(DWORD samplingRate);




//��������  �E�B���h�E���֐�  ��������

//�X���[���[�h�؂�ւ�<�g�p�s��>
//@deprecated
void  SlowMode(bool mode);

//�X���[���[�h���x�ݒ�<�g�p�s��>
//@deprecated
void  SlowModeSpeed(int amount);




//��������  ���̑��֗��֐�/�֐��}�N��  ��������

//���ȈՃ��b�Z�[�W�{�b�N�X
void  Message(LPCTSTR text, LPCTSTR title);

#define SafeDelete(p)      if((p)) { delete   (p);   (p) = nullptr; };
#define SafeDeleteArray(p) if((p)) { delete[] (p);   (p) = nullptr; };
#define SafeRelease(p)     if((p)) { (p)->Release(); (p) = nullptr; };



