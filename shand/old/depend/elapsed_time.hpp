// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// ※ Windows用

//------------------------------------------------------//
// Name : CElapsedTime									//
// Desc : 経過時間測定クラス							//
//														//
// Version : 1.00 2006/08/01 作成						//
//			 1.01 2006/12/14 Unicodeに対応				//
//														//
//------------------------------------------------------//

#ifndef _ELAPSED_TIME_HPP_
#define _ELAPSED_TIME_HPP_

#include <sstream>
#include <windows.h>
#include <tchar.h>

// 経過時間測定クラス
class CElapsedTime {
private:
	DWORD	m_dwStartTime;	// 開始時間
public:
	CElapsedTime()
		: m_dwStartTime(GetTickCount())
	{
	}
	
	~CElapsedTime() {};

	void ReStart()
	{
		m_dwStartTime = GetTickCount();
	}

	// 経過時間取得
	double GetElapsedTime() const
	{
		return static_cast<double>(GetTickCount() - m_dwStartTime)/1000;
	}

	// 経過時間表示
	void DispElapsedTime()
	{
		std::basic_ostringstream<TCHAR> strTime;
		strTime << GetElapsedTime() << _T("秒");
		MessageBox(NULL, strTime.str().c_str(), _T("ElapsedTime"), MB_OK);
	}
};

#endif	//_ELAPSED_TIME_HPP_

//-----使用例-----------------------------------|
//												|
//	CElapedTime tmElapsed;	// 経過時間			|
//												|
//	〜〜〜時間のかかる処理〜〜〜				|
//												|
//	// 経過時間をポップアップ表示				|
//	tmElapsed.DispElapsedTime();				|
//												|
//----------------------------------------------|

//-----使用例-----------------------------------|
//												|
//	CElapedTime tmElapsed;	// 経過時間			|
//												|
//	〜〜〜時間のかかる処理〜〜〜				|
//												|
//	// 経過時間取得								|
//	〜〜 = tmElapsed.GetElapsedTime();			|
//												|
//	〜〜経過時間を使った処理					|
//												|
//----------------------------------------------|
