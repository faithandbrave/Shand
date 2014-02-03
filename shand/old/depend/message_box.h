// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// ※ Windows用
//------------------------------------------------------//
// Name : simple_message_box							//
// Desc : 簡易メッセージボックス						//
// Note : 整数、小数表示用								//
//														//
// Version : 1.00 2006/08/04 作成						//
//			 1.01 2006/12/14 Unicodeに対応				//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#ifndef _SHAND_MESSAGEBOX_H_
#define _SHAND_MESSAGEBOX_H_

#include <windows.h>
#include <tchar.h>
#include <sstream>

template<class Type>
inline void simple_message_box(const Type& msg)
{
	std::basic_stringstream<TCHAR> interpreter;

	interpreter << msg;
	MessageBox(NULL, interpreter.str().c_str(), _T(""), MB_OK);
}

#endif	// _SHAND_MESSAGEBOX_H_

//------------------------------------------|
//				How to use					|
//------------------------------------------|
//											|
//	int n = 314;							|
//	simple_message_box(n);					|
//											|
//	double f = 3.14;						|
//	simple_message_box(f);					|
//											|
//	string s = "abc"						|
//	simple_message_box(s);					|
//											|
//------------------------------------------|
