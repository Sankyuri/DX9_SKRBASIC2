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
		HRESULT draw();

		//空のテクスチャを作成する
		HRESULT createEmptyTexture(DWORD width, DWORD height);
		
		//レンダリングターゲットを変更する
		HRESULT setRenderTarget(D3DCOLOR clearColor);

		//テクスチャを矩形切り取りする
		void  trim(float left, float top,
				float right, float bottom, float width, float height);

		//表示色を変更する
		void  setDrawColor(D3DCOLOR color);


		//アルファブレンドの方法を変更
		void  setAlphaBlendMode(D3DBLEND mode);

		//ラッピング方式を設定
		void  setWrappingMode(D3DTEXTUREADDRESS modeU, D3DTEXTUREADDRESS modeV);

		//u(x)方向のラッピング方式を設定
		void  setWrappingModeU(D3DTEXTUREADDRESS mode);

		//v(y)方向のラッピング方式を設定
		void  setWrappingModeV(D3DTEXTUREADDRESS mode);

		//ポリゴンの中心x座標を取得
		float getPolygonCX();

		//ポリゴンの中心y座標を取得
		float getPolygonCY();

		//ポリゴンの中心z座標を取得(通常は常に 0.0f を返す)<非推奨>
		//@deprecated
		float getPolygonCZ();


		//座標を設定
		void  setPos(float x, float y);
		
		//座標を設定(zあり)
		void  setPos(float x, float y, float z);
		
		//中心点を設定
		void  setCenterPos(float cx, float cy);

		//中心点を設定<非推奨>
		//@deprecated
		void  setCenterPos(float cx, float cy, float cz);

		//xの中心点を設定
		void  setCenterPosX(float cx);
		
		//yの中心点を設定
		void  setCenterPosY(float cy);
		
		//zの中心点を設定<非推奨>
		//@deprecated
		void  setCenterPosZ(float cz);

		//x軸中心の回転
		//@param angleRad ラジアン角
		void  rotateX(float angleRad);
		
		//y軸中心の回転
		void  rotateY(float angleRad);

		//z軸中心の回転
		void  rotateZ(float angleRad);

		//縦横比固定の2Dスケーリング
		void  scaling(float size);

		//2Dスケーリング
		void  scaling(float x, float y);
		
		//スケーリング
		void  scaling(float x, float y, float z);
		
		//平行移動
		void  move(float x, float y);
		
		//平行移動
		void  move(float x, float y, float z);
		
		//2次元の回転(z軸, Rad)
		void  rotate(float angleRad);
		
		//回転(Rad)
		void  rotate(Axis axis, float angleRad);
		
		//テクスチャ座標を移動する
		void  moveUV(float u, float v);
		
		//テクスチャ座標を移動する(uのみ)
		void  moveU(float u);
		
		//テクスチャ座標を移動する(vのみ)
		void  moveV(float v);

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
		HRESULT load_LoadTex(LPCTSTR SrcFile, D3DCOLOR keyColor);
		//メモリからテクスチャ読み込み
		HRESULT load_LoadTexMem(const CHAR a_data[], DWORD a_size, D3DCOLOR keyColor);
		//リソースファイルからテクスチャ読み込み
		HRESULT load_LoadTexRscFil(LPCTSTR a_pSrcFile, DWORD a_size, DWORD a_offset,
				D3DCOLOR a_keyColor);
		//リソースからテクスチャ読み込み
		HRESULT load_LoadTexRsc(int id, D3DCOLOR keyColor);

		void    matrixFinallyA(D3DXMATRIX *mtrx);      //行列最終処理
		void    matrixFinallyB(D3DXMATRIX *mtrx);      //原点に戻す処理を必要とする場合用
		void    moveForMFB(float x, float y, float z); //MatrixFinallyB用移動関数


	};

} // namespace skrBasic



