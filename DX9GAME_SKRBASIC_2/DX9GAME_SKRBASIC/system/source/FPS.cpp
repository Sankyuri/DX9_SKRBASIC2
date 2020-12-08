#include "..\header\systemExtern.h"
#include "..\header\FPS.h"

using namespace skrBasic;

float GameFPS::getFPS() {
	static float timecount;
	nowTime = timeGetTime();
	if ((timecount = (nowTime - preTime)) >= 1000) {
		prefps = (framecnt * 1000) / timecount;
		preTime = timeGetTime();
		framecnt = 0;
	} //果たしてこれで良いのだろうか……^^;
	++framecnt;
	return prefps;
}

void GameFPS::showFPS(int a_x, int a_y, int a_color) {
	showFPS_InitFont();
	float fps = getFPS();
	_stprintf(fpsFontBuf, _T("%6.2f fps"), fps);
	FPSFont.drawStringEx(fpsFontBuf, a_x, a_y, DT_LEFT, a_color);
}

void GameFPS::showFPS_InitFont() {
	if (wasInitFPSFont == false) {
		FPSFont.setFont(_T("ＭＳ　ゴシック"), 16, false);
		wasInitFPSFont = true;
	}
}




