#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\FontSimple.h"
#include "..\header\SystemParam.h"

using namespace skrBasic;

HRESULT FontSimple::setFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, &pFont))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setShadowedFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, &pFont))) {
		return E_FAIL;
	}
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, &pFontShadow))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setBorderedFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setShadowedFont(a_fontName, a_fontSize, a_isItalic))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setFontInner(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic,
	                             int a_weight, LPD3DXFONT *a_font)
{
	HRESULT hr = D3DXCreateFont(
		g_pd3dDevice,
		a_fontSize,
		0,
		a_weight,
		1,
		a_isItalic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FIXED_PITCH | FF_DONTCARE,
		a_fontName, // _T("‚l‚r@ƒSƒVƒbƒN") ‚È‚Ç
		a_font
		);
	if (FAILED(hr)) {
		Message(_T("ƒtƒHƒ“ƒg‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½"), _T("Error"));
		isCanDraw = false;
		return E_FAIL;
	}
	pFont->PreloadCharacters('a', 'z');
	pFont->PreloadCharacters('A', 'Z');
	pFont->PreloadCharacters('0', '9');
	pFont->PreloadCharacters('±', 'Ý');
	pFont->PreloadCharacters('‚ ', '‚ñ');
	pFont->PreloadCharacters('ƒA', 'ƒ“');
	isCanDraw = true;
	return S_OK;
}




void FontSimple::drawString(const TCHAR *a_string, int a_x, int a_y, D3DCOLOR a_color) {
	if (true == isCanDraw) {
		drawStringEx(a_string, a_x, a_y, DT_LEFT, a_color);
	}
}

void FontSimple::drawStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format, D3DCOLOR a_color) {
	if (true == isCanDraw) {
		drawStringInner(a_string, a_x, a_y, a_format, a_color, pFont);
	}
}

void FontSimple::drawStringInner(const TCHAR *a_string, int a_x, int a_y, int a_format, D3DCOLOR a_color, LPD3DXFONT a_font) {
	if (true == isCanDraw) {
		RECT rc = { a_x, a_y };
		a_font->DrawText(NULL, a_string, -1, &rc, DT_CALCRECT, NULL);
		a_font->DrawText(NULL, a_string, -1, &rc, a_format, a_color);
	}
}


void FontSimple::drawShadowedString(const TCHAR *a_string, int a_x, int a_y,
	                                D3DCOLOR a_color, int a_sx, int a_sy, D3DCOLOR a_scolor)
{
	drawShadowedStringEx(a_string, a_x, a_y, DT_LEFT, a_color, a_sx, a_sy, a_scolor);
}

void FontSimple::drawShadowedStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format,
	                                  D3DCOLOR a_color, int a_sx, int a_sy, D3DCOLOR a_scolor)
{
	if (true == isCanDraw) {
		drawStringInner(a_string, a_x + a_sx, a_y + a_sy, a_format, a_scolor, pFontShadow);
		drawStringInner(a_string, a_x, a_y, a_format, a_color, pFont);
	}
}


void FontSimple::drawBorderedString(const TCHAR *a_string, int a_x, int a_y,
		                            D3DCOLOR a_color, D3DCOLOR a_bcolor)
{
	drawBorderedStringEx(a_string, a_x, a_y, DT_LEFT, a_color, a_bcolor);
}

void FontSimple::drawBorderedStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format,
	                                  D3DCOLOR a_color, D3DCOLOR a_bcolor)
{
	if (true == isCanDraw) {
		drawStringInner(a_string, a_x + 2, a_y    , a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x + 2, a_y + 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x    , a_y + 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y + 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y    , a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y - 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x    , a_y - 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x + 2, a_y - 2, a_format, a_bcolor, pFontShadow);
		drawStringInner(a_string, a_x, a_y, a_format, a_color, pFont);
	}
}




FontSimple::~FontSimple() {
	SafeRelease(pFont);
	SafeRelease(pFontShadow);
}








