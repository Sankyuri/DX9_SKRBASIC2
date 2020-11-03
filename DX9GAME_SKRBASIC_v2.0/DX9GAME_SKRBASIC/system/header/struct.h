#pragma once
#include "SystemInclude.h"


//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊  構造体宣言  ＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

//＊＊＊＊＊＊＊＊  共通  ＊＊＊＊＊＊＊＊

//ポリゴンの頂点座標(座標変換済み)
typedef struct tagVERTEX_2D {
	float x, y, z; //頂点座標
	float rhw; //除算数
	DWORD color; //頂点色
	float u, v; //テクスチャ座標
} VERTEX_2D;


//画像の座標
typedef struct tagPOSITION_2D {
	D3DXVECTOR2 cPos; //現在のxy座標
	D3DXVECTOR2 center; //中心y座標
} POSITION_2D;


//画像の座標(3D)
typedef struct tagPOSITION_3D {
	D3DXVECTOR3 cPos; //現在のxy座標
	D3DXVECTOR3 center; //中心y座標
}POSITION_3D;


//画像のクロマキーを指定する
typedef struct tagALPHA_KEYCOLOR_SETTING
{
	UINT alpha_r; //赤
	UINT alpha_g; //緑
	UINT alpha_b; //青
	UINT alpha_a; //透明度
} ALPHA_KEYCOLOR_SETTING;


//画像の基本設定をする構造体
typedef struct tagTEXTURE_BASIC_SETTING
{
	TCHAR fp[255]; //ファイルへのパス
	POSITION_2D pos; //画像の座標

} TEXTURE_BASIC_SETTING;




//＊＊＊＊＊＊＊＊  背景  ＊＊＊＊＊＊＊＊
typedef struct tagBACKGROUND_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //基本設定
} BACKGROUND_SETTING;



//＊＊＊＊＊＊＊＊  キャラクター立ち絵  ＊＊＊＊＊＊＊＊

//キャラクターを設定する構造体
typedef struct tagCHARACTER_TEXTURE_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //基本設定
	int face_statement; //表情
	int position; //キャラクターの位置
	int pos_x; //x位置(position が CUSTOM の時有効)
	int pos_y; //y位置(position が CUSTOM の時有効)
	ALPHA_KEYCOLOR_SETTING key; //透過色設定

} CHARACTER_TEXTURE_SETTING;



//キャラクターを設定する構造+alpha
typedef struct tagCHARACTER_TEXTURE_SETTING_EX
{

	TEXTURE_BASIC_SETTING texBase; //基本設定
	int face_statement; //表情
	int position; //キャラクターの位置
	int pos_x; //x位置(position が CUSTOM の時有効)
	int pos_y; //y位置(position が CUSTOM の時有効)
	float angle; //角度
	float angle_accel; //角加速度
	ALPHA_KEYCOLOR_SETTING key; //透過色設定

} CHARACTER_TEXTURE_SETTING_EX;




//＊＊＊＊＊＊＊＊  ウィンドウ  ＊＊＊＊＊＊＊＊

//テキストウィンドウ
typedef struct tagTEXTWINDOW_SETTING
{
	TEXTURE_BASIC_SETTING texBase; //基本設定
	int x; //x座標
	int y; //y座標
	UCHAR base_alpha; //基本不透明度

} TEXTWINDOW_SETTING;







