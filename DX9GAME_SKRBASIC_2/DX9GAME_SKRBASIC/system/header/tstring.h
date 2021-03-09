#pragma once
#include <string>

namespace stdex {
#ifdef _UNICODE
	using _tstring        = std::wstring;
	using _tstringbuf     = std::wstringbuf;
	using _tistringstream = std::wistringstream;
	using _tostringstream = std::wostringstream;
	using _tstringstream  = std::wstringstream;
#else
	using _tstring        = std::string;
	using _tstringbuf     = std::stringbuf;
	using _tistringstream = std::istringstream;
	using _tostringstream = std::ostringstream;
	using _tstringstream  = std::stringstream;
#endif  /* _UNICODE */
}



