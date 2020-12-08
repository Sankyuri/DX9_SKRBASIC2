#pragma once
#include "ImageBase.h"

namespace skrBasic {

	//
	//  ポリゴンによる2次元描画系統
	//  ImageSprite でも描画はできるが
	//  こちらの方がより高機能になっている
	//
	class ImagePolygon : public ImageBase {
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
		HRESULT refer(ImageBase *a_obj);

		//画像を描画する
		HRESULT draw();

		//空のテクスチャを作成する
		HRESULT createEmptyTexture(DWORD a_width, DWORD a_height);
		
		//レンダリングターゲットを変更する
		HRESULT setRenderTarget(D3DCOLOR a_clearColor);

		//テクスチャを矩形切り取りし、リサイズする
		void  trim(float a_left, float a_top,
				   float a_right, float a_bottom,
				   float a_width, float a_height);

		//テクスチャを矩形切り取りする
		void  trim(float a_left, float a_top,
				   float a_right, float a_bottom);

		//板ポリゴンのサイズを設定する
		//なお、設定された中心座標を中心にリサイズされる
		void  resize(float a_width, float a_height);

		//表示色を変更する
		void  setDrawColor(D3DCOLOR a_color);


		//アルファブレンドの方法を変更
		void  setAlphaBlendMode(D3DBLEND a_mode);

		//ラッピング方式を設定
		void  setWrappingMode(D3DTEXTUREADDRESS a_modeU, D3DTEXTUREADDRESS a_modeV);

		//u(x)方向のラッピング方式を設定
		void  setWrappingModeU(D3DTEXTUREADDRESS a_mode);

		//v(y)方向のラッピング方式を設定
		void  setWrappingModeV(D3DTEXTUREADDRESS a_mode);

		//ポリゴンの中心x座標を取得
		float getPolygonCX();

		//ポリゴンの中心y座標を取得
		float getPolygonCY();

		//ポリゴンの中心z座標を取得(通常は常に 0.0f を返す)<非推奨>
		//@deprecated
		float getPolygonCZ();


		//座標を設定
		void  setPos(float a_x, float a_y);
		
		//座標を設定(zあり)
		void  setPos(float a_x, float a_y, float a_z);
		
		//中心点を設定
		void  setCenterPos(float a_cx, float a_cy);

		//中心点を設定<非推奨>
		//@deprecated
		void  setCenterPos(float a_cx, float a_cy, float a_cz);

		//xの中心点を設定
		void  setCenterPosX(float a_cx);
		
		//yの中心点を設定
		void  setCenterPosY(float a_cy);
		
		//zの中心点を設定<非推奨>
		//@deprecated
		void  setCenterPosZ(float a_cz);

		//x軸中心の回転
		//@param angleRad ラジアン角
		void  rotateX(float a_angleRad);
		
		//y軸中心の回転
		void  rotateY(float a_angleRad);

		//z軸中心の回転
		void  rotateZ(float a_angleRad);

		//縦横比固定の2Dスケーリング
		void  scaling(float a_size);

		//2Dスケーリング
		void  scaling(float a_x, float a_y);
		
		//スケーリング
		void  scaling(float a_x, float a_y, float a_z);
		
		//平行移動
		void  move(float a_x, float a_y);
		
		//平行移動
		void  move(float a_x, float a_y, float a_z);
		
		//2次元の回転(z軸, Rad)
		void  rotate(float a_angleRad);
		
		//回転(Rad)
		void  rotate(Axis a_axis, float a_angleRad);
		
		//テクスチャ座標を移動する
		void  moveUV(float a_u, float a_v);
		
		//テクスチャ座標を移動する(uのみ)
		void  moveU(float a_u);
		
		//テクスチャ座標を移動する(vのみ)
		void  moveV(float a_v);

		//座標、スケール、角度の全てをリセットする
		void  reset();
		
		//スケールをリセットする
		void  resetScale();
		
		//角度をリセットする
		void  resetAngle();
		
		//x軸回転角度をリセットする
		void  resetAngleX();
		
		//y軸回転角度をリセットする
		void  resetAngleY();
		
		//z軸回転角度をリセットする
		void  resetAngleZ();




		ImagePolygon();
		~ImagePolygon();

	private:

		LPDIRECT3DVERTEXBUFFER9  ppVtxBuf;  //頂点バッファ

		D3DXVECTOR3              rcpos;  //ポリゴン上の中心座標
		D3DTEXTUREADDRESS        sampleModeU; //u(x)方向のラッピング方式
		D3DTEXTUREADDRESS        sampleModeV; //v(y)方向のラッピング方式

		VERTEX_2D                vtx[4]; //頂点座標
		void                    *pVtx;   //頂点バッファへのポインタ

		D3DXMATRIX               mtrx_pos;    //頂点座標の行列

		HRESULT load_Common(DWORD a_width, DWORD a_height); //読み込みの共通処理

		HRESULT load_CreateVtx();    //頂点作成
		HRESULT load_CreateVtxBuf(); //頂点バッファ作成
		HRESULT copyVtx();     //VRAMに頂点情報(？)を書き込む
		HRESULT draw_SetTex(); //描画するテクスチャを設定
		//テクスチャ読み込み
		HRESULT load_LoadTex(LPCTSTR a_pSrcFile, D3DCOLOR a_keyColor);
		//メモリからテクスチャ読み込み
		HRESULT load_LoadTexMem(const BYTE a_data[], DWORD a_size, D3DCOLOR a_keyColor);
		//リソースファイルからテクスチャ読み込み
		HRESULT load_LoadTexRscFil(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
								   D3DCOLOR a_keyColor);
		//リソースからテクスチャ読み込み
		HRESULT load_LoadTexRsc(int a_id, D3DCOLOR a_keyColor);

		void    matrixFinallyA(D3DXMATRIX *a_mtrx);      //行列最終処理
		void    matrixFinallyB(D3DXMATRIX *a_mtrx);      //原点に戻す処理を必要とする場合用
		void    moveForMFB(float a_x, float a_y, float a_z); //MatrixFinallyB用移動関数


	};

} // namespace skrBasic



