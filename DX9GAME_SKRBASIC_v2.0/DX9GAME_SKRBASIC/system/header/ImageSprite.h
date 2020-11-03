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
		//@param pSrcFile 画像ファイル名
		//@param width    画像縦サイズ(px)
		//@param height   画像横サイズ(px)
		//@param keyColor 透過色
		HRESULT load(LPCTSTR pSrcFile,
				DWORD width, DWORD height, D3DCOLOR keyColor);

		//画像をメモリから読み込む
		//@param data     画像データのポイント
		//@param size     画像データのサイズ
		//@param offset   データ迄のオフセット
		//@param width    画像縦サイズ(px)
		//@param height   画像横サイズ(px)
		//@param keyColor 透過色
		HRESULT loadFromMemory(const CHAR data[], DWORD size, DWORD offset,
				DWORD width, DWORD height, D3DCOLOR keyColor);

		//画像をリソースファイルから読み込む
		//@param pSrcFile 画像ファイル名
		//@param size     画像データのサイズ
		//@param offset   データ迄のオフセット
		//@param width    画像縦サイズ(px)
		//@param height   画像横サイズ(px)
		//@param keyColor 透過色
		HRESULT loadFromResourceFile(LPCTSTR pSrcFile, DWORD size, DWORD offset,
				DWORD width, DWORD height, D3DCOLOR keyColor);

		//画像をリソースから読み込む
		//@param id       リソースID
		//@param width    画像縦サイズ(px)
		//@param height   画像横サイズ(px)
		//@param keyColor 透過色
		HRESULT loadFromResource(int id,
				DWORD width, DWORD height, D3DCOLOR keyColor);


		//テクスチャを参照で使用する
		//@param obj 参照したい ImageSprite のオブジェクト
		HRESULT refer(ImageBase *obj);


		//画像を描画する
		//@param trimSize トリミングする領域(px)
		//@param color 描画色
		HRESULT draw(const RECT *trimSize, D3DCOLOR color);

		//画像を描画する
		//@param trimSize トリミングする領域(px)
		HRESULT draw(const RECT *trimSize);

		//画像を描画する
		HRESULT draw();


		//空のテクスチャを作成する
		//レンダリングターゲットにする場合に使用
		HRESULT createEmptyTexture(DWORD width, DWORD height);

		//レンダリングターゲットを変更する
		HRESULT setRenderTarget(D3DCOLOR clearColor);

		//アルファブレンドの方法を変更
		void    alphaBlendMode(D3DBLEND mode);
	
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
		void  setPos(float x, float y);

		//中心点を設定
		void  setCenterPos(float cx, float cy);

		//縦横比固定のスケーリング
		void  scaling(float size);
		
		//スケーリング
		void  scaling(float x, float y);
		
		//平行移動
		void  move(float x, float y);
		
		//回転
		//@param angleRad ラジアン角
		void  rotate(float angleRad);

		//回転<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotate(Axis axis, float angleRad);

		//x軸中心の回転<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateX(float angleRad);

		//y軸中心の回転(SPRITEだからz軸回転だけで十分)<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateY(float angleRad);
		
		//z軸中心の回転(というかx軸回転/y軸回転は不可？)<非推奨>
		//@param angleRad ラジアン角
		//@deprecated
		void  rotateZ(float angleRad);




		ImageSprite();
		~ImageSprite();

	private:
		LPD3DXSPRITE        ppSprite;  //スプライト
		D3DXMATRIX          mtrx_temp, mtrx; //途中計算用行列、最終的な変換行列
		void                matrixFinally();  //行列最終処理

	};

} // namespace skrBasic



