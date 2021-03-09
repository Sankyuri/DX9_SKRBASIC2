#include "..\header\systemExtern.h"
#include "..\header\FPS.h"

using namespace skrBasic;

float GameFPS::getFPS() {
	static float timecount;
	m_nowTime = timeGetTime();
	if ((timecount = (m_nowTime - m_preTime)) >= 1000) {
		m_prefps = (m_framecnt * 1000) / timecount;
		m_preTime = timeGetTime();
		m_framecnt = 0;
	} //果たしてこれで良いのだろうか……^^;
	++m_framecnt;
	return m_prefps;
}

void GameFPS::showFPS(int a_x, int a_y, int a_color) {
	showFPSInitFont();
	float fps = getFPS();
	_stprintf(m_fpsFontBuf, _T("%6.2f fps"), fps);
	m_fpsFont.drawStringEx(m_fpsFontBuf, a_x, a_y, DT_LEFT, a_color);
}

void GameFPS::showFPSInitFont() {
	if (not m_wasInitFPSFont) {
		m_fpsFont.setFont(_T("ＭＳ　ゴシック"), 16, false);
		m_wasInitFPSFont = true;
	}
}




