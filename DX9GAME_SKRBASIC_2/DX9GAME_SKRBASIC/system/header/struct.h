#pragma once
#include "SystemInclude.h"


//��������������������������������  �\���̐錾  ��������������������������������

//����������������  ����  ����������������

//�|���S���̒��_���W(���W�ϊ��ς�)
typedef struct tagVERTEX_2D
{
	float m_x, m_y, m_z; //���_���W
	float m_rhw;     //���Z��
	DWORD m_color;   //���_�F
	float m_u, m_v;    //�e�N�X�`�����W
} VERTEX_2D;


//�摜�̍��W
typedef struct tagPOSITION_2D
{
	D3DXVECTOR2 m_cPos;   //���݂�xy���W
	D3DXVECTOR2 m_center; //���Sxy���W
} POSITION_2D;


//�摜�̍��W(3D)
typedef struct tagPOSITION_3D
{
	D3DXVECTOR3 m_cPos;   //���݂�xy���W
	D3DXVECTOR3 m_center; //���Sxy���W
}POSITION_3D;


//�摜�̃N���}�L�[���w�肷��
typedef struct tagALPHA_KEYCOLOR
{
	UINT m_r; //��
	UINT m_g; //��
	UINT m_b; //��
	UINT m_a; //�����x
} ALPHA_KEYCOLOR;


//�摜�̊�{�ݒ������\����
typedef struct tagTEXTURE_BASIC_SETTING
{
	TCHAR       m_fp[255]; //�t�@�C���ւ̃p�X
	POSITION_2D m_pos;     //�摜�̍��W

} TEXTURE_BASIC_SETTING;




//����������������  �w�i  ����������������
typedef struct tagBACKGROUND_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //��{�ݒ�
} BACKGROUND_SETTING;



//����������������  �L�����N�^�[�����G  ����������������

//�L�����N�^�[��ݒ肷��\����
typedef struct tagCHARACTER_TEXTURE_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //��{�ݒ�
	int m_faceStatement; //�\��
	int m_position; //�L�����N�^�[�̈ʒu
	int m_x; //x�ʒu(position �� CUSTOM �̎��L��)
	int m_y; //y�ʒu(position �� CUSTOM �̎��L��)
	ALPHA_KEYCOLOR m_key; //���ߐF�ݒ�

} CHARACTER_TEXTURE_SETTING;



//�L�����N�^�[��ݒ肷��\��+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX
{

	TEXTURE_BASIC_SETTING m_texBase; //��{�ݒ�
	int m_faceStatement; //�\��
	int m_position; //�L�����N�^�[�̈ʒu
	int m_x; //x�ʒu(position �� CUSTOM �̎��L��)
	int m_y; //y�ʒu(position �� CUSTOM �̎��L��)
	float m_angle; //�p�x
	float m_angleAccel;   //�p�����x
	ALPHA_KEYCOLOR m_key; //���ߐF�ݒ�

} CHARACTER_TEXTURE_SETTING_EX;




//����������������  �E�B���h�E  ����������������

//�e�L�X�g�E�B���h�E
typedef struct tagTEXTWINDOW_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //��{�ݒ�
	int m_x; //x���W
	int m_y; //y���W
	UCHAR m_baseAlpha; //��{�s�����x

} TEXTWINDOW_SETTING;







