#ifndef COMMON_FILE_CONTROL_INCLUDE
#define COMMON_FILE_CONTROL_INCLUDE

// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <shand/tokenizer.hpp>

//--------------------------------------------------//
// 名称 : FindFile()								//
// 用途 : ファイルの存在チェック					//
// 引数 : ファイルパス								//
// 戻値 : TRUE:ファイルあり FALSE:なし				//
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
// 名称 : IsFilePath()								//
// 用途 : 指定パスがファイルパスか判断				//
// 引数 : パス(ディレクトリ or ファイル				//
// 戻値 : TRUE:ファイルパス FALSE:ディレクトリパス	//
//--------------------------------------------------//
inline BOOL IsFilePath(LPCTSTR pszPath)
{
	shand::tokenizer token(pszPath, _T("\\"));
	return token[token.size() -1].find(_T(".")) != -1;
}


//--------------------------------------------------//
// 名称 : AddWildCard()								//
// 用途 : パスにワイルドカード付加					//
// 引数 : パス										//
// 戻値 : ワイルドカード付加パス					//
//--------------------------------------------------//
inline CString AddWildCard(CString strPath)
{
	if (!IsFilePath(strPath))
		strPath += _T("\\*.*");
	return strPath;
}


//--------------------------------------------------//
// 名称 : GetDirectoryInFiles()						//
// 用途 : フォルダ内のファイル名一覧取得			//
// 引数 : フォルダパス								//
// 戻値 : ファイル名一覧							//
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
// 名称 : DeleteDirectory()							//
// 用途 : 指定ディレクトリ削除(サブディレクトリ含め)//
// 引数 : ディレクトリのパス						//
// 戻値 : TRUE:削除成功 FALSE:削除失敗				//
//--------------------------------------------------//
inline BOOL DeleteDirectory(LPCTSTR pszDirPath)
{
	CFileFind	objFileFind;
	CString		strDirPath = pszDirPath;

	// 該当ディレクトリなし
	if (!objFileFind.FindFile(AddWildCard(strDirPath), 0))
		return FALSE;

	BOOL bFind = TRUE;
	while(bFind)
	{
		bFind = objFileFind.FindNextFile();

		// ファイル名が"."か".."の場合は次を検索
		if (objFileFind.IsDots())
			continue;

		// 削除するファイル名取得
		CString strDeleteFile = pszDirPath;
		strDeleteFile += _T("\\") + objFileFind.GetFileName();

		// フォルダだった場合、再帰呼び出しでそのフォルダを削除
		if(objFileFind.IsDirectory())
			DeleteDirectory(strDeleteFile);

		// ファイルの削除
		else
			::DeleteFile(strDeleteFile);
	}
	objFileFind.Close();

	// フォルダの削除
	return ::RemoveDirectory(pszDirPath);
}

//--------------------------------------------------//
// 名称 : DeleteDirectoryInFiles()					//
// 用途 : 指定ディレクトリ内のファイル削除			//
// 引数 : ディレクトリのパス						//
// 戻値 : TRUE:削除成功 FALSE:削除失敗				//
//--------------------------------------------------//
inline BOOL DeleteDirectoryInFiles(LPCTSTR pszDirPath)
{
	CFileFind	objFileFind;
	CString		strDirPath = pszDirPath;

	// 該当ディレクトリなし
	if (!objFileFind.FindFile(AddWildCard(strDirPath), 0))
		return FALSE;

	BOOL bFind = TRUE;
	while(bFind)
	{
		bFind = objFileFind.FindNextFile();

		// ファイル名が"."か".."の場合は次を検索
		if (objFileFind.IsDots())
			continue;

		// ファイル削除
		if(!objFileFind.IsDirectory())
			::DeleteFile(objFileFind.GetFilePath());
	}
	objFileFind.Close();

	return TRUE;
}

#endif // COMMON_FILE_CONTROL_INCLUDE

