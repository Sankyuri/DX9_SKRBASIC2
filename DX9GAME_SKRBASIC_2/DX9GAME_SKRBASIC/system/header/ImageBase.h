#pragma once
#include "systemExtern.h"
#include "..\param\Axis.h"
#include "..\param\MouseInput.h"

namespace skrBasic {

	//
	//  ImageSprite と ImagePolygon の汎化クラス
	//
	class ImageBase {
	public:
		//画像を読み込む
		//@param pSrcFile 画像ファイル名
		//@param width    画像縦サイズ(px)
		//@param height   画像横サイズ(px)
		//@param keyColor 透過色
		virtual HRESULT load(LPCTSTR a_pSrcFile, DWORD a_width, DWORD a_height,
							 D3DCOLOR a_keyColor) = 0;

		//画像を描画する
		virtual HRESULT draw() = 0;
		
		//テクスチャを参照で使用する
		//@param obj 参照したい ImageSprite のオブジェクト
		virtual HRESULT refer(ImageBase *a_obj) = 0;


		//画像の幅を取得
		int   getImgWidth();

		//画像の高さを取得
		int   getImgHeight();

		//x座標を取得
		float getPosX();

		//y座標を取得
		float getPosY();

		//z座標を取得(通常は常に 0.0f を返す)<非推奨>
		//@deprecated
		float getPosZ();

		//中心x座標を取得
		float getCenterX();

		//中心y座標を取得
		float getCenterY();

		//中心z座標を取得(通常は常に 0.0f を返す)<非推奨>
		//@deprecated
		float getCenterZ();

		//x軸スケールを取得
		float getScaleX();

		//y軸スケールを取得
		float getScaleY();

		//z軸スケールを取得
		float getScaleZ();

		//x軸角度を取得
		float getAngleX();

		//y軸角度を取得
		float getAngleY();

		//z軸角度を取得
		float getAngleZ();




		//拡縮したか
		bool isScaled();
		
		//回転したか
		bool isRotated();




		//マウスで画像をホバーしているか
		bool isMouseHoverOn();

		//マウスで画像をクリックしているか
		bool isMouseInputOn(MouseInput a_mousebutton);

		//マウスで画像をクリックしたか
		bool isMouseClickOn(MouseInput a_mousebutton);

		//マウスで画像をクリックするのを離したか
		bool isMouseReleaseOn(MouseInput a_mousebutton);

		//マウスで画像に何らかの入力をしたか
		bool isSomeMouseOn();




		ImageBase();
		virtual ~ImageBase();


		//テクスチャを取得<システム用>
		//@deprecated
		LPDIRECT3DTEXTURE9 getTexture();

	protected:
		bool                m_isDrawable;     //描画できるか

		LPDIRECT3DTEXTURE9  m_ppTexture;     //テクスチャ
		ImageBase          *m_pReferTexture; //テクスチャを参照使用

		D3DVIEWPORT9        m_vpSurf;        //レンダリングターゲット変更用ビューポート
		LPDIRECT3DSURFACE9  m_rtSurf;        //レンダリングターゲット変更用サーフェイス
		LPDIRECT3DSURFACE9  m_zbSurf;        //レンダリングターゲット変更用Zバッファサーフェイス

		LONG                m_width;         //画像幅
		LONG                m_height;        //画像高さ
		D3DXVECTOR3         m_pos;           //座標
		D3DXVECTOR3         m_cpos;          //中心座標
		D3DXVECTOR3         m_scale;         //拡大率
		D3DXVECTOR3         m_angle;         //角度

		D3DBLEND            m_blendMode;     //アルファブレンドの方式

		D3DXMATRIX          m_mtrxMove;     //平行移動行列
		D3DXMATRIX          m_mtrxScale;    //拡大縮小行列
		D3DXMATRIX          m_mtrxRotate;   //回転行列


	private:
		//角度が0の時のカーソルの相対位置( isMouseHover() 用)
		POINT getRelativePoint(const POINT *a_curPos);

	};

}



