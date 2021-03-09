#pragma once
#include "FontSimple.h"

namespace skrBasic {

	//
	//  FPSカウンタ
	//
	class GameFPS {
	public:
		float getFPS(); //fps数取得
		void  showFPS(int a_x, int a_y, int a_color); //fps数表示

	private:
		skrBasic::FontSimple m_fpsFont; //FPS表示用フォント
		bool  m_wasInitFPSFont; //FPS表示用フォントの初期化をやったか
		TCHAR m_fpsFontBuf[16]; //FPS表示用
		DWORD m_preTime;        //計測開始時間
		DWORD m_nowTime;        //現在の時間
		int   m_timecnt;        //経過時間
		int   m_framecnt;       //フレーム数
		float m_prefps;         //前回のFPS

		void  showFPSInitFont(); //FPS表示用フォント初期化

	};

}



