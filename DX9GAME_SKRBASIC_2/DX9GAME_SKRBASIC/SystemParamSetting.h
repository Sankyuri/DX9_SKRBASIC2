#pragma once
#include <Windows.h>
#include <d3d9types.h>
#include <tchar.h>
#include "system/header/tstring.h"

namespace skrBasic {

	//
	//  システムに必須の定数
	//  設定するにはそれぞれの値を変更して下さい
	//
	class SystemParamSetting {
	protected:
		//ウィンドウ(vp)の横幅
		static inline constexpr const int WINDOW_WIDTH  = 1280;

		//ウィンドウ(vp)の縦幅
		static inline constexpr const int WINDOW_HEIGHT =  720;

		//ウィンドウのタイトル
		static inline const           stdex::_tstring GAME_TITLE
						= _T("楽しい楽しいノベルゲーム");

		//DSound のPバッファのサンプリングレート
		static inline constexpr const DWORD DSOUND_SAMPLINGRATE = 44100;

		//ウィンドウのクリア色
		static inline                 D3DCOLOR clearColor
						= D3DCOLOR_XRGB(0x00, 0x63, 0x58);




	};

}

