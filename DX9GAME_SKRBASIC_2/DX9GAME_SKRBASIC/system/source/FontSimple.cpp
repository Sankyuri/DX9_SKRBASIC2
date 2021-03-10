#include "..\header\Basic.h"
#include "..\header\systemExtern.h"
#include "..\header\FontSimple.h"
#include "..\header\SystemParam.h"

using namespace skrBasic;

HRESULT FontSimple::setFont(LPCTSTR a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, m_pFont))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setShadowedFont(LPCTSTR a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, m_pFont))) {
		return E_FAIL;
	}
	if (FAILED(setFontInner(a_fontName, a_fontSize, a_isItalic, FW_NORMAL, m_pFontShadow))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setBorderedFont(LPCTSTR a_fontName, int a_fontSize, bool a_isItalic) {
	if (FAILED(setShadowedFont(a_fontName, a_fontSize, a_isItalic))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT FontSimple::setFontInner(LPCTSTR a_fontName, int a_fontSize, bool a_isItalic,
	                             int a_weight, LPD3DXFONT &a_font)
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
		&a_font
		);
	if (FAILED(hr)) {
		Message(_T("ƒtƒHƒ“ƒg‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½"), _T("Error"));
		m_isDrawable = false;
		return E_FAIL;
	}
	m_pFont->PreloadCharacters('a', 'z');
	m_pFont->PreloadCharacters('A', 'Z');
	m_pFont->PreloadCharacters('0', '9');
	m_pFont->PreloadCharacters('±', 'Ý');
	m_pFont->PreloadCharacters('‚ ', '‚ñ');
	m_pFont->PreloadCharacters('ƒA', 'ƒ“');
	m_isDrawable = true;
	return S_OK;
}




void FontSimple::drawString(LPCTSTR a_string, int a_x, int a_y, D3DCOLOR a_color) {
	if (m_isDrawable) {
		drawStringEx(a_string, a_x, a_y, DT_LEFT, a_color);
	}
}

void FontSimple::drawStringEx(LPCTSTR a_string, int a_x, int a_y, int a_format, D3DCOLOR a_color) {
	if (m_isDrawable) {
		drawStringInner(a_string, a_x, a_y, a_format, a_color, m_pFont);
	}
}

void FontSimple::drawStringInner(LPCTSTR a_string, int a_x, int a_y, int a_format, D3DCOLOR a_color, LPD3DXFONT &a_font) {
	if (m_isDrawable) {
		RECT rc = { a_x, a_y };
		a_font->DrawText(NULL, a_string, -1, &rc, DT_CALCRECT, NULL);
		a_font->DrawText(NULL, a_string, -1, &rc, a_format, a_color);
	}
}


void FontSimple::drawShadowedString(LPCTSTR a_string, int a_x, int a_y,
	                                D3DCOLOR a_color, int a_sx, int a_sy, D3DCOLOR a_scolor)
{
	drawShadowedStringEx(a_string, a_x, a_y, DT_LEFT, a_color, a_sx, a_sy, a_scolor);
}

void FontSimple::drawShadowedStringEx(LPCTSTR a_string, int a_x, int a_y, int a_format,
	                                  D3DCOLOR a_color, int a_sx, int a_sy, D3DCOLOR a_scolor)
{
	if (m_isDrawable) {
		drawStringInner(a_string, a_x + a_sx, a_y + a_sy, a_format, a_scolor, m_pFontShadow);
		drawStringInner(a_string, a_x, a_y, a_format, a_color, m_pFont);
	}
}


void FontSimple::drawBorderedString(LPCTSTR a_string, int a_x, int a_y,
		                            D3DCOLOR a_color, D3DCOLOR a_bcolor)
{
	drawBorderedStringEx(a_string, a_x, a_y, DT_LEFT, a_color, a_bcolor);
}

void FontSimple::drawBorderedStringEx(LPCTSTR a_string, int a_x, int a_y, int a_format,
	                                  D3DCOLOR a_color, D3DCOLOR a_bcolor)
{
	if (m_isDrawable) {
		drawStringInner(a_string, a_x + 2, a_y    , a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x + 2, a_y + 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x    , a_y + 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y + 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y    , a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x - 2, a_y - 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x    , a_y - 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x + 2, a_y - 2, a_format, a_bcolor, m_pFontShadow);
		drawStringInner(a_string, a_x, a_y, a_format, a_color, m_pFont);
	}
}




FontSimple::~FontSimple() {
	SafeRelease(m_pFont);
	SafeRelease(m_pFontShadow);
}








