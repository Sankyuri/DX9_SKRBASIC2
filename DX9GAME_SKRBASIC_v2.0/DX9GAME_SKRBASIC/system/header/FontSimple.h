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
		HRESULT setFont(const TCHAR *fontName, int fontSize, bool isItalic);

		//影付きセットアップ
		HRESULT setShadowedFont(const TCHAR *fontName, int fontSize, bool isItalic);

		//疑似縁取りセットアップ<非推奨>
		//@deprecated
		HRESULT setBorderedFont(const TCHAR *fontName, int fontSize, bool isItalic);


		//通常描画
		void    drawString(const TCHAR *string, int x, int y, D3DCOLOR color);
		
		//書式指定して通常描画
		void    drawStringEx(const TCHAR *string, int x, int y, int format, D3DCOLOR color);
		

		//影付き描画
		void    drawShadowedString(const TCHAR *string, int x, int y, D3DCOLOR color, int sx, int sy, D3DCOLOR scolor);

		//書式指定して影付き描画
		void    drawShadowedStringEx(const TCHAR *string, int x, int y, int format,
									 D3DCOLOR color, int sx, int sy, D3DCOLOR scolor);


		//疑似縁取り描画<非推奨>
		//@deprecated
		void    drawBorderedString(const TCHAR *string, int x, int y, D3DCOLOR color, D3DCOLOR bcolor);

		//書式指定して疑似縁取り描画<非推奨>
		//@deprecated
		void    drawBorderedStringEx(const TCHAR *string, int x, int y, int format, D3DCOLOR color, D3DCOLOR bcolor);




		~FontSimple();

	private:
		LPD3DXFONT pFont; //フォント本体
		LPD3DXFONT pFontShadow; //フォントの影など用
		bool       isCanDraw;   //表示できるか


		//セットアップ(内部処理用)
		HRESULT setFontInner(const TCHAR *fontName, int fontSize, bool isItalic,
							 int weight, LPD3DXFONT *font);
		//描画(内部処理用)
		void    drawStringInner(const TCHAR *string, int x, int y, int format,
							    D3DCOLOR color, LPD3DXFONT font);
		

	};

} // namespace skrBasic



