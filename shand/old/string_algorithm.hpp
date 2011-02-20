#ifndef SHAND_STRING_ALGORITHM_INCLUDE
#define SHAND_STRING_ALGORITHM_INCLUDE

//------------------------------------------------------//
// Name : string_algorithm								//
// Desc : ������֘A�A���S���Y��						//
//														//
// Version : 1.00 2007/05/17 �쐬						//
// Version : 1.01 2007/10/25 Simple Numeric Access�ǉ�	//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2007 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#include <string>
#include <sstream>

#pragma warning(disable : 4996)

namespace shand {

// string �� wstring
inline std::wstring to_wstr(const std::string& astr)
{
	setlocale(LC_ALL, "japanese");
	std::wstring wstr(mbstowcs(0, astr.c_str(), 0) + 1, 0);
	mbstowcs(&wstr[0], astr.c_str(), wstr.size());

	return wstr;
}


// wstring �� string
inline std::string to_astr(const std::wstring& wstr)
{
	setlocale(LC_ALL, "japanese");
	std::string astr(wcstombs(0, wstr.c_str(), 0) + 1, 0);
	wcstombs(&astr[0], wstr.c_str(), astr.size());

	return astr;
}


// wstring �� string(�󔒖���)
inline std::string to_fill_astr(const std::wstring& wstr, int fill_size)
{
	std::string astr = to_astr(wstr);

	while (static_cast<int>(astr.length()) < fill_size)
		astr += ' ';

	return astr;
}


// �E�̗]�����폜
inline std::string  trim_right(std::string& source)  { source.erase(source.find_last_not_of(' ')+1);  return source; }
inline std::wstring trim_right(std::wstring& source) { source.erase(source.find_last_not_of(L' ')+1); return source; }


// ���̗]�����폜
inline std::string  trim_left(std::string& source)  { source.erase(0, source.find_first_not_of(' '));  return source; }
inline std::wstring trim_left(std::wstring& source) { source.erase(0, source.find_first_not_of(L' ')); return source; }


//--------------------------------------------------//
// ���� : replace()									//
// �p�r : ������u��								//
// ���� : token  : �u�����镶����					//
//		  oldstr : �u���Ώ�							//
//		  newstr : �u��������						//
// �ߒl : �u���㕶����								//
//--------------------------------------------------//
template <class TString>
TString replace(const TString &target, const TString &oldstr, const TString &newstr)
{
	TString result(target);
	for (TString::size_type pos = 0; TString::npos != (pos = result.find(oldstr, pos)); pos += newstr.size()) {
		if (pos >= result.size() - oldstr.size())
			result.replace(pos, oldstr.size(), TString());
		else
			result.replace(pos, oldstr.size(), newstr);
	}
	return result;
}

//------------------------------------------------------//
//					How to use							//
//======================================================//
// string before = "123a123b";							//
// string after = replace<string>(before, "123", "A");	//
//------------------------------------------------------//



//--------------------------------------------------//
// ���� : to_string() / to_wstring()				//
// �p�r : �w�肳�ꂽ�l�𕶎���ɕϊ�				//
// ���� : ������ϊ�����l							//
// �ߒl : �ϊ��㕶����								//
//--------------------------------------------------//
template <class Type>
inline std::string to_string(const Type& target)
{
	std::stringstream interpreter;
	interpreter << target;
	return interpreter.str();
}

template <class Type>
inline std::wstring to_wstring(const Type& target)
{
	std::wstringstream interpreter;
	interpreter << target;
	return interpreter.str();
}


// string to numeric
inline int		stoi(const std::string& str) { return atoi(str.c_str()); }
inline long		stol(const std::string& str) { return atol(str.c_str()); }
inline float	stof(const std::string& str) { return static_cast<float>(atof(str.c_str())); }
inline double	stod(const std::string& str) { return atof(str.c_str()); }

// wstring to numeric
inline int		stoi(const std::wstring& str) { return _wtoi(str.c_str()); }
inline long		stol(const std::wstring& str) { return _wtol(str.c_str()); }

#if !defined(_MSC_VER) || (_MSC_VER > 1300)  // 1300 == VC++ 7.0
inline float	stof(const std::wstring& str) { return static_cast<float>(_wtof(str.c_str())); }
inline double	stod(const std::wstring& str) { return _wtof(str.c_str()); }
#endif

} // namespace shand

#pragma warning(default : 4996)

#endif // SHAND_STRING_ALGORITHM_INCLUDE
