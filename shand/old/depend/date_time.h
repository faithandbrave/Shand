#ifndef _DATETIME_H_
#define _DATETIME_H_

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "cstring_format.h"


//----------------------------------------------//
// 名称 : GetDateTimeString()					//
// 用途 : フォーマット指定した日時文字列取得	//
// 引数 : strFormat	: 日時フォーマット			//
//						%Y : 年	YYYY			//
//						%m : 月	mm				//
//						%D : 日 DD				//
//						%H : 時 HH				//
//						%M : 分 MM				//
//						%S : 秒 SS				//
//		  tmDateTime: 指定時間(未指定は現在日時)//
// 戻値 : 日時文字列							//
// メモ : WinCEでCOleDateTime::Format(...)が	//
//		  未サポートのため作成					//
//----------------------------------------------//
inline CString GetDateTimeString(CString strFormat,
								 const COleDateTime &tmDateTime=COleDateTime::GetCurrentTime())
{
	strFormat.Replace(_T("%Y"), FormatString(_T("%04d"), tmDateTime.GetYear()));
	strFormat.Replace(_T("%m"), FormatString(_T("%02d"), tmDateTime.GetMonth()));
	strFormat.Replace(_T("%D"), FormatString(_T("%02d"), tmDateTime.GetDay()));
	strFormat.Replace(_T("%d"), FormatString(_T("%02d"), tmDateTime.GetDay()));
	strFormat.Replace(_T("%H"), FormatString(_T("%02d"), tmDateTime.GetHour()));
	strFormat.Replace(_T("%M"), FormatString(_T("%02d"), tmDateTime.GetMinute()));
	strFormat.Replace(_T("%S"), FormatString(_T("%02d"), tmDateTime.GetSecond()));
	return strFormat;
}


/*----------------------------------------------|
|				How to use						|
|-----------------------------------------------|
|												|
| SetWindowText(GetDateTimeString("%Y/%m/%D"));	|
|												|
|	|---------------------------|				|
|	| 2006/01/01				|				|
|	|---------------------------|				|
|												|
|----------------------------------------------*/


#endif // _DATETIME_H_
