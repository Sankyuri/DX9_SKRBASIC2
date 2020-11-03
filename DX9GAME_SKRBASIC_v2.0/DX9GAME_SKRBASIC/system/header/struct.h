#pragma once
#include "SystemInclude.h"


//��������������������������������  �\���̐錾  ��������������������������������

//����������������  ����  ����������������

//�|���S���̒��_���W(���W�ϊ��ς�)
typedef struct tagVERTEX_2D {
	float x, y, z; //���_���W
	float rhw; //���Z��
	DWORD color; //���_�F
	float u, v; //�e�N�X�`�����W
} VERTEX_2D;


//�摜�̍��W
typedef struct tagPOSITION_2D {
	D3DXVECTOR2 cPos; //���݂�xy���W
	D3DXVECTOR2 center; //���Sy���W
} POSITION_2D;


//�摜�̍��W(3D)
typedef struct tagPOSITION_3D {
	D3DXVECTOR3 cPos; //���݂�xy���W
	D3DXVECTOR3 center; //���Sy���W
}POSITION_3D;


//�摜�̃N���}�L�[���w�肷��
typedef struct tagALPHA_KEYCOLOR_SETTING
{
	UINT alpha_r; //��
	UINT alpha_g; //��
	UINT alpha_b; //��
	UINT alpha_a; //�����x
} ALPHA_KEYCOLOR_SETTING;


//�摜�̊�{�ݒ������\����
typedef struct tagTEXTURE_BASIC_SETTING
{
	TCHAR fp[255]; //�t�@�C���ւ̃p�X
	POSITION_2D pos; //�摜�̍��W

} TEXTURE_BASIC_SETTING;




//����������������  �w�i  ����������������
typedef struct tagBACKGROUND_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //��{�ݒ�
} BACKGROUND_SETTING;



//����������������  �L�����N�^�[�����G  ����������������

//�L�����N�^�[��ݒ肷��\����
typedef struct tagCHARACTER_TEXTURE_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //��{�ݒ�
	int face_statement; //�\��
	int position; //�L�����N�^�[�̈ʒu
	int pos_x; //x�ʒu(position �� CUSTOM �̎��L��)
	int pos_y; //y�ʒu(position �� CUSTOM �̎��L��)
	ALPHA_KEYCOLOR_SETTING key; //���ߐF�ݒ�

} CHARACTER_TEXTURE_SETTING;



//�L�����N�^�[��ݒ肷��\��+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX
{

	TEXTURE_BASIC_SETTING texBase; //��{�ݒ�
	int face_statement; //�\��
	int position; //�L�����N�^�[�̈ʒu
	int pos_x; //x�ʒu(position �� CUSTOM �̎��L��)
	int pos_y; //y�ʒu(position �� CUSTOM �̎��L��)
	float angle; //�p�x
	float angle_accel; //�p�����x
	ALPHA_KEYCOLOR_SETTING key; //���ߐF�ݒ�

} CHARACTER_TEXTURE_SETTING_EX;




//����������������  �E�B���h�E  ����������������

//�e�L�X�g�E�B���h�E
typedef struct tagTEXTWINDOW_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //��{�ݒ�
	int x; //x���W
	int y; //y���W
	UCHAR base_alpha; //��{�s�����x

} TEXTWINDOW_SETTING;







