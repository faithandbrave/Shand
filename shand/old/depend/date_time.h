#ifndef _DATETIME_H_
#define _DATETIME_H_

#include "cstring_format.h"


//----------------------------------------------//
// ���� : GetDateTimeString()					//
// �p�r : �t�H�[�}�b�g�w�肵������������擾	//
// ���� : strFormat	: �����t�H�[�}�b�g			//
//						%Y : �N	YYYY			//
//						%m : ��	mm				//
//						%D : �� DD				//
//						%H : �� HH				//
//						%M : �� MM				//
//						%S : �b SS				//
//		  tmDateTime: �w�莞��(���w��͌��ݓ���)//
// �ߒl : ����������							//
// ���� : WinCE��COleDateTime::Format(...)��	//
//		  ���T�|�[�g�̂��ߍ쐬					//
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