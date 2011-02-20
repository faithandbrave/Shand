// ※ RTTIを使いたくないのでボツ

//------------------------------------------------------//
// Name : lexical_cast<Type>(Source)					//
// Desc : 数字 ⇔ 文字列の相互変換						//
//		  型変換をキャストと同じくらい簡単にする		//
// Note : boost::lexical_castのアレンジ版				//
//		  以下に対応									//
//		  ・空文字列から数字への変換					//
//		  ・小数点文字列から整数への変換				//
//														//
// Version : 1.00 2006/07/27 作成						//
//			 1.01 2006/12/14 Unicodeに対応				//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#ifndef _SHAND_LEXICAL_CAST_HPP_
#define _SHAND_LEXICAL_CAST_HPP_

#include <sstream>
#include <string>
#include <tchar.h>

#pragma warning(disable:4700)

namespace shand {
	
namespace detail {
	//----------------------------------------------//
	// 名称 : check_type()							//
	// 用途 : 変数の型チェック						//
	// 引数 : チェックする変数						//
	// 戻値 : 1:整数 2:小数 3:文字列 -1:それ以外	//
	//----------------------------------------------//
	template <class T>
	int check_type(T target)
	{
		// 指定された変数の型情報取得
		const std::type_info& target_type = typeid(target);
		
		// 整数
		if (target_type == typeid(signed	int)	||
			target_type == typeid(unsigned	int)	||
			target_type == typeid(signed	long)	||
			target_type == typeid(unsigned	long)	||
			target_type == typeid(signed	short)	||
			target_type == typeid(unsigned	short))
			return 1;

		// 小数
		if (target_type == typeid(float)	||
			target_type == typeid(double))
			return 2;

		// 文字列
		if (target_type == typeid(signed	char)		||
			target_type == typeid(unsigned	char)		||
			target_type == typeid(signed	char *)		||
			target_type == typeid(unsigned	char *)		||
			target_type == typeid(char *)				||
			target_type == typeid(char const *)			||
			target_type == typeid(wchar_t *)			||
			target_type == typeid(wchar_t const *)		||
			target_type == typeid(std::string)			||
			target_type == typeid(std::wstring))
			return 3;

		return -1;
	}
} // namespace detail

	//----------------------------------------------//
	// 名称 : lexical_cast<>()						//
	// 用途 : 数字 ⇔ 文字列の相互変換				//
	// 引数 : <Target>	: 指定された型へ変換		//
	//		  src		: 変換する値				//
	// 戻値 : 変換された値							//
	//----------------------------------------------//
	template <class Type, class Source>
	Type lexical_cast(Source src)
	{
		using namespace std;
		using namespace shand::detail;

		Type						result = Type();
		basic_stringstream<TCHAR>	interpreter;

		// 空文字列から数字への変換は0とする
		if((check_type(result)	== 1 || check_type(result) == 2) &&
			check_type(src)		== 3) {
			interpreter << src;
			if (interpreter.str() == _T("")) {
				interpreter.str(_T(""));
				interpreter << _T("0");
				interpreter >> result;
				return result;
			}
		}

		interpreter.str(_T(""));

		// 小数文字列から整数への変換
		if (check_type(result)	== 1 &&
			(check_type(src)	== 3 || check_type(src) == 2)) {
			basic_string<TCHAR> decimal;
			interpreter << src;
			decimal = interpreter.str();
			interpreter.str(_T(""));

			if (decimal.find(_T('.')) != string::npos) {
				interpreter << _ttoi(decimal.c_str());
				interpreter >> result;
				return result;
			}
		}

		// 型変換
		if (!(interpreter << src)		||
			!(interpreter >> result)	||
			!(interpreter >> std::ws).eof())
			throw std::runtime_error("bad lexical_cast()");

		return result;
	}

	template <> char			lexical_cast(const char&			src) { return src; }
	template <> int				lexical_cast(const int&				src) { return src; }
	template <> long			lexical_cast(const long&			src) { return src; }
	template <> unsigned char	lexical_cast(const unsigned char&	src) { return src; }
	template <> unsigned int	lexical_cast(const unsigned int&	src) { return src; }
	template <> unsigned long	lexical_cast(const unsigned long&	src) { return src; }
	template <> double			lexical_cast(const double&			src) { return src; }
	template <> float			lexical_cast(const float&			src) { return src; }
	template <> std::string		lexical_cast(const std::string&		src) { return src; }

}	// namespace shand

#pragma warning(default:4700)

/*------------------------------------------------------|
|					How to use							|
|=======================================================|
|														|
|	// string to number									|
|	int nNo = lexical_cast<int>("314");					|
|														|
|	// number to string									|
|	std::string strNo = lexical_cast<std::string>(314);	|
|														|
|														|
|	※ CAUTION!!!										|
|														|
|	try {												|
|		int nNo = lexical_cast<int>("abc");				|
|	}													|
|	catch(std::exception const &e) {					|
|		std::cout << e.what() << std::endl;				|
|	}													|
|														|
|------------------------------------------------------*/

#endif // _SHAND_LEXICAL_CAST_HPP_

