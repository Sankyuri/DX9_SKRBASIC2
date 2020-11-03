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
		virtual HRESULT load(LPCTSTR pSrcFile,
			DWORD width, DWORD height, D3DCOLOR keyColor) = 0;

		//画像を描画する
		virtual HRESULT draw() = 0;
		
		//テクスチャを参照で使用する
		//@param obj 参照したい ImageSprite のオブジェクト
		virtual HRESULT refer(ImageBase *obj) = 0;


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
		bool isMouseInputOn(MouseInput mousebutton);

		//マウスで画像をクリックしたか
		bool isMouseClickOn(MouseInput mousebutton);

		//マウスで画像をクリックするのを離したか
		bool isMouseReleaseOn(MouseInput mousebutton);

		//マウスで画像に何らかの入力をしたか
		bool isSomeMouseOn();

		


		//テクスチャを取得<システム用>
		//@deprecated
		LPDIRECT3DTEXTURE9 getTexture();

	protected:
		bool                isCanDraw;     //描画できるか

		LPDIRECT3DTEXTURE9  ppTexture;     //テクスチャ
		ImageBase          *pReferTexture; //テクスチャを参照使用

		D3DVIEWPORT9        vpSurf;        //レンダリングターゲット変更用ビューポート
		LPDIRECT3DSURFACE9  rtSurf;        //レンダリングターゲット変更用サーフェイス
		LPDIRECT3DSURFACE9  zbSurf;        //レンダリングターゲット変更用Zバッファサーフェイス

		LONG                width;         //画像幅
		LONG                height;        //画像高さ
		D3DXVECTOR3         pos;           //座標
		D3DXVECTOR3         cpos;          //中心座標
		D3DXVECTOR3         scale;         //拡大率
		D3DXVECTOR3         angle;         //角度

		D3DBLEND            blendMode;     //アルファブレンドの方式

		D3DXMATRIX          mtrx_move;     //平行移動行列
		D3DXMATRIX          mtrx_scale;    //拡大縮小行列
		D3DXMATRIX          mtrx_rotate;   //回転行列


	private:
		//角度が0の時のカーソルの相対位置( isMouseHover() 用)
		POINT getRelativePoint(const POINT *curPos);

	};

}



