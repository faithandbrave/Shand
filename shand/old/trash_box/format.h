// ※ VC++6.0用
//------------------------------------------------------//
// Name : format()										//
// Desc : 指定したフォーマットの文字列取得				//
//														//
// Version : 1.00 2006/08/01 作成						//
//			 1.01 2006/08/03 Unicode対応版追加			//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#ifndef _SHAND_FORMAT_H_
#define _SHAND_FORMAT_H_

#pragma warning(disable:4996)	// ～が古い形式として宣言されました

inline char* format(const char *szFormat, ...)
{
	char	*szBuff = NULL;
	int		nSize	= 0;

	szBuff = (char*)realloc(szBuff, 64);

	while (szBuff && _vsnprintf(szBuff, nSize - 1, szFormat, (char*)(&szFormat + 1)) < 0) {
		szBuff = (char*)realloc(szBuff, nSize + 128);
		nSize += 128;
	}
	return szBuff;
}


inline wchar_t *format(const wchar_t *szFormat, ...)
{
	wchar_t	*szBuff	= NULL;
	int		nSize	= 0;

	szBuff = (wchar_t*)realloc(szBuff, 64);

	while (szBuff && _vsnwprintf(szBuff, nSize - 1, szFormat, va_list(&szFormat + 1)) < 0) {
		szBuff = (wchar_t*)realloc(szBuff, nSize + 128);
		nSize += 128;
	}
	return szBuff;
}

#pragma warning(default:4996)

#endif // _SHAND_FORMAT_H_


/*------------------------------------------------------|
|					How to Use							|
|-------------------------------------------------------|
|														|
|	int nNo = 314;										|
|	MessageBox(NULL, format("%d", nNo), "", MB_OK);		|
|														|
-------------------------------------------------------*/

