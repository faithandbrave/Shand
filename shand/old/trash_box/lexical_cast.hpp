// �� RTTI���g�������Ȃ��̂Ń{�c

//------------------------------------------------------//
// Name : lexical_cast<Type>(Source)					//
// Desc : ���� �� ������̑��ݕϊ�						//
//		  �^�ϊ����L���X�g�Ɠ������炢�ȒP�ɂ���		//
// Note : boost::lexical_cast�̃A�����W��				//
//		  �ȉ��ɑΉ�									//
//		  �E�󕶎��񂩂琔���ւ̕ϊ�					//
//		  �E�����_�����񂩂琮���ւ̕ϊ�				//
//														//
// Version : 1.00 2006/07/27 �쐬						//
//			 1.01 2006/12/14 Unicode�ɑΉ�				//
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
	// ���� : check_type()							//
	// �p�r : �ϐ��̌^�`�F�b�N						//
	// ���� : �`�F�b�N����ϐ�						//
	// �ߒl : 1:���� 2:���� 3:������ -1:����ȊO	//
	//----------------------------------------------//
	template <class T>
	int check_type(T target)
	{
		// �w�肳�ꂽ�ϐ��̌^���擾
		const std::type_info& target_type = typeid(target);
		
		// ����
		if (target_type == typeid(signed	int)	||
			target_type == typeid(unsigned	int)	||
			target_type == typeid(signed	long)	||
			target_type == typeid(unsigned	long)	||
			target_type == typeid(signed	short)	||
			target_type == typeid(unsigned	short))
			return 1;

		// ����
		if (target_type == typeid(float)	||
			target_type == typeid(double))
			return 2;

		// ������
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
	// ���� : lexical_cast<>()						//
	// �p�r : ���� �� ������̑��ݕϊ�				//
	// ���� : <Target>	: �w�肳�ꂽ�^�֕ϊ�		//
	//		  src		: �ϊ�����l				//
	// �ߒl : �ϊ����ꂽ�l							//
	//----------------------------------------------//
	template <class Type, class Source>
	Type lexical_cast(Source src)
	{
		using namespace std;
		using namespace shand::detail;

		Type						result = Type();
		basic_stringstream<TCHAR>	interpreter;

		// �󕶎��񂩂琔���ւ̕ϊ���0�Ƃ���
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

		// ���������񂩂琮���ւ̕ϊ�
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

		// �^�ϊ�
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
|	�� CAUTION!!!										|
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

