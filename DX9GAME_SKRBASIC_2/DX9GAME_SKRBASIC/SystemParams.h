#pragma once
#include "system/header/SystemParam.h"

namespace skrBasic {

	//
	//  システムに必須の定数
	//  設定するにはそれぞれの値を変更して下さい
	//

	//ウィンドウ(vp)の横幅
	const int SystemParam::WINDOW_WIDTH  = 1280;

	//ウィンドウ(vp)の縦幅
	const int SystemParam::WINDOW_HEIGHT =  720;

	//ウィンドウのタイトル
	const std::_tstring SystemParam::GAME_TITLE = _T("楽しい楽しいノベルゲーム");

	//DSound のPバッファのサンプリングレート
	const DWORD SystemParam::DSOUND_SAMPLINGRATE = 44100;

	//ウィンドウのクリア色
	D3DCOLOR SystemParam::clearColor = D3DCOLOR_XRGB(0x00, 0x63, 0x58);

}

