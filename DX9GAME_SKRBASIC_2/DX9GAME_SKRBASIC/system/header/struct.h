#pragma once
#include "SystemInclude.h"


//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  構造体宣言  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

//＊＊＊＊＊＊＊＊  共通  ＊＊＊＊＊＊＊＊

//ポリゴンの頂点座標(座標変換済み)
typedef struct tagVERTEX_2D
{
	float m_x, m_y, m_z; //頂点座標
	float m_rhw;     //除算数
	DWORD m_color;   //頂点色
	float m_u, m_v;    //テクスチャ座標
} VERTEX_2D;


//画像の座標
typedef struct tagPOSITION_2D
{
	D3DXVECTOR2 m_cPos;   //現在のxy座標
	D3DXVECTOR2 m_center; //中心xy座標
} POSITION_2D;


//画像の座標(3D)
typedef struct tagPOSITION_3D
{
	D3DXVECTOR3 m_cPos;   //現在のxy座標
	D3DXVECTOR3 m_center; //中心xy座標
}POSITION_3D;


//画像のクロマキーを指定する
typedef struct tagALPHA_KEYCOLOR
{
	UINT m_r; //赤
	UINT m_g; //緑
	UINT m_b; //青
	UINT m_a; //透明度
} ALPHA_KEYCOLOR;


//画像の基本設定をする構造体
typedef struct tagTEXTURE_BASIC_SETTING
{
	TCHAR       m_fp[255]; //ファイルへのパス
	POSITION_2D m_pos;     //画像の座標

} TEXTURE_BASIC_SETTING;




//＊＊＊＊＊＊＊＊  背景  ＊＊＊＊＊＊＊＊
typedef struct tagBACKGROUND_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //基本設定
} BACKGROUND_SETTING;



//＊＊＊＊＊＊＊＊  キャラクター立ち絵  ＊＊＊＊＊＊＊＊

//キャラクターを設定する構造体
typedef struct tagCHARACTER_TEXTURE_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //基本設定
	int m_faceStatement; //表情
	int m_position; //キャラクターの位置
	int m_x; //x位置(position が CUSTOM の時有効)
	int m_y; //y位置(position が CUSTOM の時有効)
	ALPHA_KEYCOLOR m_key; //透過色設定

} CHARACTER_TEXTURE_SETTING;



//キャラクターを設定する構造+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX
{

	TEXTURE_BASIC_SETTING m_texBase; //基本設定
	int m_faceStatement; //表情
	int m_position; //キャラクターの位置
	int m_x; //x位置(position が CUSTOM の時有効)
	int m_y; //y位置(position が CUSTOM の時有効)
	float m_angle; //角度
	float m_angleAccel;   //角加速度
	ALPHA_KEYCOLOR m_key; //透過色設定

} CHARACTER_TEXTURE_SETTING_EX;




//＊＊＊＊＊＊＊＊  ウィンドウ  ＊＊＊＊＊＊＊＊

//テキストウィンドウ
typedef struct tagTEXTWINDOW_SETTING
{
	TEXTURE_BASIC_SETTING m_texBase; //基本設定
	int m_x; //x座標
	int m_y; //y座標
	UCHAR m_baseAlpha; //基本不透明度

} TEXTWINDOW_SETTING;







