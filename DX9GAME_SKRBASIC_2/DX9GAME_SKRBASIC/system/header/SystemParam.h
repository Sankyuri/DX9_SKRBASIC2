#pragma once
#include "../../SystemParamSetting.h"

namespace skrBasic {

	//
	//  システムに必須の定数
	//
	class SystemParam : public SystemParamSetting {
	public:
		//ウィンドウの幅を取得
		//@return ウィンドウ(ビューポート)の幅
		static inline constexpr const int getWindowWidth() {
			return WINDOW_WIDTH;
		}

		//ウィンドウの高さを取得
		//@return ウィンドウ(ビューポート)の高さ
		static inline constexpr const int getWindowHeight() {
			return WINDOW_HEIGHT;
		}

		//ウィンドウのタイトルを取得
		//@return ウィンドウのタイトル
		static inline constexpr const stdex::_tstring getWindowTitle() {
			return GAME_TITLE;
		}

		//DSound のプライマリバッファのサンプリングレートを取得
		//@return DSound のプライマリバッファのサンプリングレート
		static inline constexpr const DWORD getDSPBufSamplingRate() {
			return DSOUND_SAMPLINGRATE;
		}

		//ウィンドウのクリア色を取得
		static inline constexpr const D3DCOLOR getClearColor() {
			return clearColor;
		}

		//ウィンドウのクリア色を設定
		static inline void setClearColor(D3DCOLOR a_color) {
			clearColor = a_color;
		}




		//ウィンドウのクリア色を設定
		static inline constexpr const int getSKRBasicVersion() {
			return SKRB_VER;
		}




	private:
		static inline constexpr const int SKRB_VER = 235; // version 2.35

		SystemParam() = delete;


	};

}; // namespace skrBasic



