#pragma once
#include "SystemInclude.h"
#include "tstring.h"

namespace skrBasic {

	//
	//  システムに必須の定数
	//
	class SystemParam {
	public:
		//ウィンドウの幅を取得
		//@return ウィンドウ(ビューポート)の幅
		static int getWindowWidth();

		//ウィンドウの高さを取得
		//@return ウィンドウ(ビューポート)の高さ
		static int getWindowHeight();

		//ウィンドウのタイトルを取得
		//@return ウィンドウのタイトル
		static stdex::_tstring getWindowTitle();

		//DSound のプライマリバッファのサンプリングレートを取得
		//@return DSound のプライマリバッファのサンプリングレート
		static DWORD getDSPBufSamplingRate();

		//ウィンドウのクリア色を設定
		static void  setClearColor(D3DCOLOR a_color);

		//ウィンドウのクリア色を取得
		static D3DCOLOR getClearColor();


		SystemParam() = delete;

	private:
		//ウィンドウ(vp)の横幅
		static const int WINDOW_WIDTH;
		//ウィンドウ(vp)の縦幅
		static const int WINDOW_HEIGHT;
		//ウィンドウのタイトル
		static const stdex::_tstring GAME_TITLE;
		//DSound のPバッファのサンプリングレート
		static const DWORD DSOUND_SAMPLINGRATE;
		//ウィンドウのクリア色
		static       D3DCOLOR clearColor;

	};

}; // namespace skrBasic



