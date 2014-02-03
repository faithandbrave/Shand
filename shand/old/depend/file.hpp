#ifndef COMMON_FILE_CONTROL_INCLUDE
#define COMMON_FILE_CONTROL_INCLUDE

// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <shand/tokenizer.hpp>

//--------------------------------------------------//
// ���� : FindFile()								//
// �p�r : �t�@�C���̑��݃`�F�b�N					//
// ���� : �t�@�C���p�X								//
// �ߒl : TRUE:�t�@�C������ FALSE:�Ȃ�				//
//--------------------------------------------------//
inline BOOL FindFile(LPCTSTR pszFilePath)
{
	HANDLE hFind=NULL;
	WIN32_FIND_DATA fd; 

	hFind = FindFirstFile(pszFilePath, &fd);
	BOOL bFind = hFind != INVALID_HANDLE_VALUE;

	FindClose(hFind);
	return bFind;
}


//--------------------------------------------------//
// ���� : IsFilePath()								//
// �p�r : �w��p�X���t�@�C���p�X�����f				//
// ���� : �p�X(�f�B���N�g�� or �t�@�C��				//
// �ߒl : TRUE:�t�@�C���p�X FALSE:�f�B���N�g���p�X	//
//--------------------------------------------------//
inline BOOL IsFilePath(LPCTSTR pszPath)
{
	shand::tokenizer token(pszPath, _T("\\"));
	return token[token.size() -1].find(_T(".")) != -1;
}


//--------------------------------------------------//
// ���� : AddWildCard()								//
// �p�r : �p�X�Ƀ��C���h�J�[�h�t��					//
// ���� : �p�X										//
// �ߒl : ���C���h�J�[�h�t���p�X					//
//--------------------------------------------------//
inline CString AddWildCard(CString strPath)
{
	if (!IsFilePath(strPath))
		strPath += _T("\\*.*");
	return strPath;
}


//--------------------------------------------------//
// ���� : GetDirectoryInFiles()						//
// �p�r : �t�H���_���̃t�@�C�����ꗗ�擾			//
// ���� : �t�H���_�p�X								//
// �ߒl : �t�@�C�����ꗗ							//
//--------------------------------------------------//
inline std::vector<CString> GetDirectoryInFiles(const CString& strDirPath)
{
	WIN32_FIND_DATA			stFindData;
	std::vector<CString>	vFiles;

	HANDLE hFindFile = FindFirstFile(AddWildCard(strDirPath), &stFindData);
	while(hFindFile != INVALID_HANDLE_VALUE) {
		if(!(stFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			CString strFile = stFindData.cFileName;
			if (!strFile.IsEmpty() && strFile[0] != _T('.'))
				vFiles.push_back(strFile);
		}

		if(!FindNextFile(hFindFile, &stFindData))
			break;
	}

	if(hFindFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFindFile);

	return vFiles;
}


//--------------------------------------------------//
// ���� : DeleteDirectory()							//
// �p�r : �w��f�B���N�g���폜(�T�u�f�B���N�g���܂�)//
// ���� : �f�B���N�g���̃p�X						//
// �ߒl : TRUE:�폜���� FALSE:�폜���s				//
//--------------------------------------------------//
inline BOOL DeleteDirectory(LPCTSTR pszDirPath)
{
	CFileFind	objFileFind;
	CString		strDirPath = pszDirPath;

	// �Y���f�B���N�g���Ȃ�
	if (!objFileFind.FindFile(AddWildCard(strDirPath), 0))
		return FALSE;

	BOOL bFind = TRUE;
	while(bFind)
	{
		bFind = objFileFind.FindNextFile();

		// �t�@�C������"."��".."�̏ꍇ�͎�������
		if (objFileFind.IsDots())
			continue;

		// �폜����t�@�C�����擾
		CString strDeleteFile = pszDirPath;
		strDeleteFile += _T("\\") + objFileFind.GetFileName();

		// �t�H���_�������ꍇ�A�ċA�Ăяo���ł��̃t�H���_���폜
		if(objFileFind.IsDirectory())
			DeleteDirectory(strDeleteFile);

		// �t�@�C���̍폜
		else
			::DeleteFile(strDeleteFile);
	}
	objFileFind.Close();

	// �t�H���_�̍폜
	return ::RemoveDirectory(pszDirPath);
}

//--------------------------------------------------//
// ���� : DeleteDirectoryInFiles()					//
// �p�r : �w��f�B���N�g�����̃t�@�C���폜			//
// ���� : �f�B���N�g���̃p�X						//
// �ߒl : TRUE:�폜���� FALSE:�폜���s				//
//--------------------------------------------------//
inline BOOL DeleteDirectoryInFiles(LPCTSTR pszDirPath)
{
	CFileFind	objFileFind;
	CString		strDirPath = pszDirPath;

	// �Y���f�B���N�g���Ȃ�
	if (!objFileFind.FindFile(AddWildCard(strDirPath), 0))
		return FALSE;

	BOOL bFind = TRUE;
	while(bFind)
	{
		bFind = objFileFind.FindNextFile();

		// �t�@�C������"."��".."�̏ꍇ�͎�������
		if (objFileFind.IsDots())
			continue;

		// �t�@�C���폜
		if(!objFileFind.IsDirectory())
			::DeleteFile(objFileFind.GetFilePath());
	}
	objFileFind.Close();

	return TRUE;
}

#endif // COMMON_FILE_CONTROL_INCLUDE

