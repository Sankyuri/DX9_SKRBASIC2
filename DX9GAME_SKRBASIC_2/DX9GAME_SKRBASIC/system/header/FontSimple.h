#pragma once
#include "SystemInclude.h"

namespace skrBasic {

	//
	//  フォントオブジェクトによる文字表示系統
	//  フォントオブジェクトはかなり遅いらしく、
	//  主に簡易的な文字表示に用いる
	//
	class FontSimple {
	public:
		//通常セットアップ
		HRESULT setFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic);

		//影付きセットアップ
		HRESULT setShadowedFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic);

		//疑似縁取りセットアップ<非推奨>
		//@deprecated
		HRESULT setBorderedFont(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic);


		//通常描画
		void    drawString(const TCHAR *a_string, int a_x, int a_y, D3DCOLOR a_color);
		
		//書式指定して通常描画
		void    drawStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format, D3DCOLOR a_color);
		

		//影付き描画
		void    drawShadowedString(const TCHAR *a_string, int a_x, int a_y, D3DCOLOR a_color,
								   int a_sx, int a_sy, D3DCOLOR a_scolor);

		//書式指定して影付き描画
		void    drawShadowedStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format,
									 D3DCOLOR a_color, int a_sx, int a_sy, D3DCOLOR a_scolor);


		//疑似縁取り描画<非推奨>
		//@deprecated
		void    drawBorderedString(const TCHAR *a_string, int a_x, int a_y,
								   D3DCOLOR a_color, D3DCOLOR a_bcolor);

		//書式指定して疑似縁取り描画<非推奨>
		//@deprecated
		void    drawBorderedStringEx(const TCHAR *a_string, int a_x, int a_y, int a_format,
									 D3DCOLOR a_color, D3DCOLOR a_bcolor);




		~FontSimple();

	private:
		LPD3DXFONT pFont; //フォント本体
		LPD3DXFONT pFontShadow; //フォントの影など用
		bool       isCanDraw;   //表示できるか


		//セットアップ(内部処理用)
		HRESULT setFontInner(const TCHAR *a_fontName, int a_fontSize, bool a_isItalic,
							 int a_weight, LPD3DXFONT *a_font);
		//描画(内部処理用)
		void    drawStringInner(const TCHAR *a_string, int a_x, int a_y, int a_format,
							    D3DCOLOR a_color, LPD3DXFONT a_font);
		

	};

} // namespace skrBasic



