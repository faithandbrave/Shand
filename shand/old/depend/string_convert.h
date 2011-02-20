#ifndef _STRING_CONVERT_H_
#define _STRING_CONVERT_H_

//�� MFC, ATL/WTL�p

#pragma warning(disable : 4530)
#include <string>
#include <vector>
#pragma warning(default : 4530)

#include <atlbase.h>
#include <atlconv.h>

//--------------------------------------//
// char* �� std::string�ւ̃L���X�g		//
// �\���̂̃����o�����񂩂�̕ϊ��Ɏg�p	//
//--------------------------------------//
#define STRING_CAST(String) std::string(String, String + sizeof(String))
#define CHAR_CAST(Character) std::string(1, Character)


//------------------------------------------//
// �E�̋󔒂�����							//
//------------------------------------------//
template<class String>
inline String TrimRight(String& strSrc)
{
	strSrc.erase(strSrc.find_last_not_of(' ')+1);
	return strSrc;
}


//------------------------------------------//
// ���̋󔒂�����							//
//------------------------------------------//
template<class String>
inline String TrimLeft(String& strSrc)
{
	strSrc.erase(0, strSrc.find_first_not_of(' '));
	return strSrc;
}


//------------------------------------------//
// ���� : ToMultStr()						//
// �p�r : wchar_t*(Unicode) �� char*(ANSI)	//
// ���� : Unicode������						//
// �ߒl : ASNI������						//
//------------------------------------------//
inline std::string ToMultStr(const std::wstring &strWide)
{
	USES_CONVERSION;
	return W2A(strWide.c_str());
}


//------------------------------------------//
// ���� : ToWideStr()						//
// �p�r : char*(ASNI) �� wchar_t*(Unicode)	//
// ���� : ANSI������						//
// �ߒl : Unicode������						//
//------------------------------------------//
inline std::wstring ToWideStr(const std::string &strMult)
{
	USES_CONVERSION;
	return A2W(strMult.c_str());
}


//------------------------------------------//
// ���� : ToWideInt()						//
// �p�r : char*(ASNI) �� int				//
// ���� : ANSI������						//
// �ߒl : �ϊ����ꂽ�����l					//
//------------------------------------------//
inline int ToWideInt(const std::string &strMult)
{
	return _wtoi(ToWideStr(strMult).c_str());
}


//------------------------------------------//
// ���� : ToWideInt()						//
// �p�r : char*(ASNI) �� long				//
// ���� : ANSI������						//
// �ߒl : �ϊ����ꂽ�����l					//
//------------------------------------------//
inline long ToWideLong(const std::string &strMult)
{
	return _wtol(ToWideStr(strMult).c_str());
}

/*
//------------------------------------------//
// ���� : ToWideDouble()					//
// �p�r : char*(ASNI) �� double				//
// ���� : ANSI������						//
// �ߒl : �ϊ����ꂽ�����l					//
//------------------------------------------//
inline double ToWideDouble(const std::string &strMult)
{
	return _wtof(ToWideStr(strMult).c_str());
}
*/

//------------------------------------------//
// ���� : ToMemWideStr()					//
// �p�r : wchar_t*(Unicode) �� char*(ANSI)	//
//		  �w�肳�ꂽ�������X�y�[�X���߂�	//
// ���� : strWide	: Unicode������			//
//		  nMemCount	: �O���߂��錅��		//
// �ߒl : ANSI������						//
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
// ���� : ToMemWideStr()					//
// �p�r : int �� char*(ANSI)				//
//		  �w�肳�ꂽ�������O���߂�			//
// ���� : nWide		: �ϊ����鐮���l		//
//		  nMemCount : �O���ߌ���			//
// �ߒl : ANSI������						//
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
// ���� : WriteWideString()					//
// �p�r : ���C�h�����񏑍���				//
// ���� : pTargetFile	: �������ރt�@�C��	//
//		  pszWriteBuff	: �������ޕ�����	//
// �ߒl : �Ȃ�								//
//------------------------------------------//
inline void WriteWideString(CFile *pTargetFile, const wchar_t* pszWriteBuff)
{
	std::string strMult(ToMultStr(pszWriteBuff));
	pTargetFile->Write(strMult.c_str(), static_cast<int>(strMult.size()));
}


#endif	// _STRING_CONVERT_H_

