#pragma once
#include "ImageBase.h"

namespace skrBasic {

	//
	//  スプライトによる2次元描画系統
	//  ポリゴンで描画するより幾らか時間が掛かるらしいので
	//  特に理由が無ければ ImagePolygon を用いても良い
	//
	class ImageSprite : public ImageBase {
	public:
		//画像を読み込む
		//@param a_pSrcFile 画像ファイル名
		//@param a_width    画像縦サイズ(px)
		//@param a_height   画像横サイズ(px)
		//@param a_keyColor 透過色
		HRESULT load(LPCTSTR a_pSrcFile, DWORD a_width, DWORD a_height,
					 D3DCOLOR a_keyColor);

		//画像をメモリから読み込む
		//@param a_data     画像データのポイント
		//@param a_size     画像データのサイズ
		//@param a_offset   データ迄のオフセット
		//@param a_width    画像縦サイズ(px)
		//@param a_height   画像横サイズ(px)
		//@param a_keyColor 透過色
		HRESULT loadFromMemory(const BYTE a_data[], DWORD a_size, DWORD a_offset,
							   DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor);

		//画像をリソースファイルから読み込む
		//@param a_pSrcFile 画像ファイル名
		//@param a_size     画像データのサイズ
		//@param a_offset   データ迄のオフセット
		//@param a_width    画像縦サイズ(px)
		//@param a_height   画像横サイズ(px)
		//@param a_keyColor 透過色
		HRESULT loadFromResourceFile(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
									 DWORD a_width, DWORD a_height, D3DCOLOR a_keyColor);

		//画像をリソースから読み込む
		//@param a_id       リソースID
		//@param a_width    画像縦サイズ(px)
		//@param a_height   画像横サイズ(px)
		//@param a_keyColor 透過色
		HRESULT loadFromResource(int a_id, DWORD a_width, DWORD a_height,
								 D3DCOLOR a_keyColor);


		//テクスチャを参照で使用する
		//@param a_obj 参照したい ImageSprite のオブジェクト
		HRESULT refer(ImageBase &a_obj);


		//画像を描画する
		//@param a_trimSize トリミングする領域(px) : nullptr 可能
		//@param a_color 描画色
		HRESULT draw(const RECT *a_trimSize, D3DCOLOR a_color);

		//画像を描画する
		//@param a_trimSize トリミングする領域(px) : nullptr 可能
		HRESULT draw(const RECT *a_trimSize);

		//画像を描画する
		HRESULT draw();


		//空のテクスチャを作成する
		//レンダリングターゲットにする場合に使用
		HRESULT createEmptyTexture(DWORD a_width, DWORD a_height);

		//レンダリングターゲットを変更する
		HRESULT setRenderTarget(D3DCOLOR a_clearColor);

		//アルファブレンドの方法を変更
		void    alphaBlendMode(D3DBLEND a_mode);
	
		//角度を取得
		float   getAngle();
	
		//x軸角度を取得<非推奨>
		//@deprecated
		float   getAngleX();
	
		//y軸角度を取得<非推奨>
		//@deprecated
		float   getAngleY();
	
		//z軸角度を取得<非推奨>
		//@deprecated
		float   getAngleZ();

		//中心点を設定
		void  setPos(float a_x, float a_y);

		//中心点を設定
		void  setCenterPos(float a_cx, float a_cy);

		//縦横比固定のスケーリング
		void  scaling(float a_size);
		
		//スケーリング
		void  scaling(float a_x, float a_y);
		
		//平行移動
		void  move(float a_x, float a_y);
		
		//回転
		//@param angleRad ラジアン角
		void  rotate(float a_angleRad);

		//回転<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotate(Axis a_axis, float a_angleRad);

		//x軸中心の回転<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateX(float a_angleRad);

		//y軸中心の回転(SPRITEだからz軸回転だけで十分)<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateY(float a_angleRad);
		
		//z軸中心の回転(というかx軸回転/y軸回転は不可？)<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateZ(float a_angleRad);




		ImageSprite();
		virtual ~ImageSprite();

	private:
		LPD3DXSPRITE m_ppSprite;  //スプライト
		D3DXMATRIX   m_mtrxTemp, m_mtrx; //途中計算用行列、最終的な変換行列

		void         matrixFinally();  //行列最終処理

	};

} // namespace skrBasic



