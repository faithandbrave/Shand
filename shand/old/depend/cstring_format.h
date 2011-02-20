#ifndef	_CSTRING_FORMAT_H_
#define _CSTRING_FORMAT_H_

// Å¶ MFC, ATL/WTLóp

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
