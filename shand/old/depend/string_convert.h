#ifndef _STRING_CONVERT_H_
#define _STRING_CONVERT_H_

//※ MFC, ATL/WTL用

#pragma warning(disable : 4530)
#include <string>
#include <vector>
#pragma warning(default : 4530)

#include <atlbase.h>
#include <atlconv.h>

//--------------------------------------//
// char* → std::stringへのキャスト		//
// 構造体のメンバ文字列からの変換に使用	//
//--------------------------------------//
#define STRING_CAST(String) std::string(String, String + sizeof(String))
#define CHAR_CAST(Character) std::string(1, Character)


//------------------------------------------//
// 右の空白を除去							//
//------------------------------------------//
template<class String>
inline String TrimRight(String& strSrc)
{
	strSrc.erase(strSrc.find_last_not_of(' ')+1);
	return strSrc;
}


//------------------------------------------//
// 左の空白を除去							//
//------------------------------------------//
template<class String>
inline String TrimLeft(String& strSrc)
{
	strSrc.erase(0, strSrc.find_first_not_of(' '));
	return strSrc;
}


//------------------------------------------//
// 名称 : ToMultStr()						//
// 用途 : wchar_t*(Unicode) → char*(ANSI)	//
// 引数 : Unicode文字列						//
// 戻値 : ASNI文字列						//
//------------------------------------------//
inline std::string ToMultStr(const std::wstring &strWide)
{
	USES_CONVERSION;
	return W2A(strWide.c_str());
}


//------------------------------------------//
// 名称 : ToWideStr()						//
// 用途 : char*(ASNI) → wchar_t*(Unicode)	//
// 引数 : ANSI文字列						//
// 戻値 : Unicode文字列						//
//------------------------------------------//
inline std::wstring ToWideStr(const std::string &strMult)
{
	USES_CONVERSION;
	return A2W(strMult.c_str());
}


//------------------------------------------//
// 名称 : ToWideInt()						//
// 用途 : char*(ASNI) → int				//
// 引数 : ANSI文字列						//
// 戻値 : 変換された整数値					//
//------------------------------------------//
inline int ToWideInt(const std::string &strMult)
{
	return _wtoi(ToWideStr(strMult).c_str());
}


//------------------------------------------//
// 名称 : ToWideInt()						//
// 用途 : char*(ASNI) → long				//
// 引数 : ANSI文字列						//
// 戻値 : 変換された整数値					//
//------------------------------------------//
inline long ToWideLong(const std::string &strMult)
{
	return _wtol(ToWideStr(strMult).c_str());
}

/*
//------------------------------------------//
// 名称 : ToWideDouble()					//
// 用途 : char*(ASNI) → double				//
// 引数 : ANSI文字列						//
// 戻値 : 変換された小数値					//
//------------------------------------------//
inline double ToWideDouble(const std::string &strMult)
{
	return _wtof(ToWideStr(strMult).c_str());
}
*/

//------------------------------------------//
// 名称 : ToMemWideStr()					//
// 用途 : wchar_t*(Unicode) → char*(ANSI)	//
//		  指定された文字数スペース埋める	//
// 引数 : strWide	: Unicode文字列			//
//		  nMemCount	: ０埋めする桁数		//
// 戻値 : ANSI文字列						//
//------------------------------------------//
inline std::string ToMemMultStr(const std::wstring &strWide, int nMemCount)
{
	USES_CONVERSION;
	std::string strMult(W2A(strWide.c_str()));

	while (static_cast<int>(strMult.size()) < nMemCount)
		strMult += ' ';

	return strMult;
}


//------------------------------------------//
// 名称 : ToMemWideStr()					//
// 用途 : int → char*(ANSI)				//
//		  指定された文字数０埋める			//
// 引数 : nWide		: 変換する整数値		//
//		  nMemCount : ０埋め桁数			//
// 戻値 : ANSI文字列						//
//------------------------------------------//
inline std::string ToMemMultStr(int nWide, int nMemCount)
{
	CString strFmt;
	strFmt.Format(_T("%d"), nWide);

	std::string strMult(ToMultStr(std::wstring(static_cast<LPCTSTR>(strFmt))));

	while (static_cast<int>(strMult.size()) < nMemCount)
		strMult = '0' + strMult;
//		strMult.insert(0, 1, '0');

	return strMult;
}


//------------------------------------------//
// 名称 : WriteWideString()					//
// 用途 : ワイド文字列書込み				//
// 引数 : pTargetFile	: 書き込むファイル	//
//		  pszWriteBuff	: 書き込む文字列	//
// 戻値 : なし								//
//------------------------------------------//
inline void WriteWideString(CFile *pTargetFile, const wchar_t* pszWriteBuff)
{
	std::string strMult(ToMultStr(pszWriteBuff));
	pTargetFile->Write(strMult.c_str(), static_cast<int>(strMult.size()));
}


#endif	// _STRING_CONVERT_H_

