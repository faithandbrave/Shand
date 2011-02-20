// �� Windows�p

//------------------------------------------------------//
// Name : CElapsedTime									//
// Desc : �o�ߎ��ԑ���N���X							//
//														//
// Version : 1.00 2006/08/01 �쐬						//
//			 1.01 2006/12/14 Unicode�ɑΉ�				//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//

#ifndef _ELAPSED_TIME_HPP_
#define _ELAPSED_TIME_HPP_

#include <sstream>
#include <windows.h>
#include <tchar.h>

// �o�ߎ��ԑ���N���X
class CElapsedTime {
private:
	DWORD	m_dwStartTime;	// �J�n����
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

	// �o�ߎ��Ԏ擾
	double GetElapsedTime() const
	{
		return static_cast<double>(GetTickCount() - m_dwStartTime)/1000;
	}

	// �o�ߎ��ԕ\��
	void DispElapsedTime()
	{
		std::basic_ostringstream<TCHAR> strTime;
		strTime << GetElapsedTime() << _T("�b");
		MessageBox(NULL, strTime.str().c_str(), _T("ElapsedTime"), MB_OK);
	}
};

#endif	//_ELAPSED_TIME_HPP_

//-----�g�p��-----------------------------------|
//												|
//	CElapedTime tmElapsed;	// �o�ߎ���			|
//												|
//	�`�`�`���Ԃ̂����鏈���`�`�`				|
//												|
//	// �o�ߎ��Ԃ��|�b�v�A�b�v�\��				|
//	tmElapsed.DispElapsedTime();				|
//												|
//----------------------------------------------|

//-----�g�p��-----------------------------------|
//												|
//	CElapedTime tmElapsed;	// �o�ߎ���			|
//												|
//	�`�`�`���Ԃ̂����鏈���`�`�`				|
//												|
//	// �o�ߎ��Ԏ擾								|
//	�`�` = tmElapsed.GetElapsedTime();			|
//												|
//	�`�`�o�ߎ��Ԃ��g��������					|
//												|
//----------------------------------------------|