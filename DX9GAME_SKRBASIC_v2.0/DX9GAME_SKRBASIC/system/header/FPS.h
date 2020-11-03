#pragma once
#include "FontSimple.h"

namespace skrBasic {

	//
	//  FPSカウンタ
	//
	class GameFPS {
	public:
		float getFPS(); //fps数取得
		void  showFPS(int x, int y, int color); //fps数表示

	private:
		skrBasic::FontSimple FPSFont; //FPS表示用フォント
		bool  wasInitFPSFont; //FPS表示用フォントの初期化をやったか
		TCHAR fpsFontBuf[16]; //FPS表示用
		DWORD preTime;        //計測開始時間
		DWORD nowTime;        //現在の時間
		int   timecnt;        //経過時間
		int   framecnt;       //フレーム数
		float prefps;         //前回のFPS

		void  showFPS_InitFont(); //FPS表示用フォント初期化

	};

}



