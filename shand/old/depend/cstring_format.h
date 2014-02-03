#ifndef	_CSTRING_FORMAT_H_
#define _CSTRING_FORMAT_H_

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// ※ MFC, ATL/WTL用

inline CString FormatString(LPCTSTR lpszFormat, ...)
{
	CString strFmt;

	va_list argList;
	va_start(argList, lpszFormat);
	strFmt.FormatV(lpszFormat, argList);
	return strFmt;
}

//------------------------------------------//
// sample									//
//==========================================//
// AfxMessageBox(FormatString("%d", 314));	//
//											//
// CString str = FormatString("%f", 3.14);	//
//------------------------------------------//

#endif	// _CSTRING_FORMAT_H_
