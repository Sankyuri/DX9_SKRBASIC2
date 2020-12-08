#pragma once
#include <string>

#ifndef _INC_TSTRING // include guard for 3rd party interop
#define _INC_TSTRING

namespace std {
#ifdef _UNICODE
	using _tstring = wstring;
	using _tstringbuf = wstringbuf;
	using _tistringstream = wistringstream;
	using _tostringstream = wostringstream;
	using _tstringstream = wstringstream;
#else
	using _tstring = string;
	using _tstringbuf = stringbuf;
	using _tistringstream = istringstream;
	using _tostringstream = ostringstream;
	using _tstringstream = stringstream;
#endif  /* _UNICODE */
}
#endif  /* _INC_TSTRING */

