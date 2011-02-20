//------------------------------------------------------//
// Name : CVector<Type>									//
// Desc : 可変長配列クラス								//
// Note : std::vectorを、MFCのCArray風にラップしたクラス//
//														//
// Version : 1.00 2006/09/20 作成						//
// Version : 1.01 2006/11/10 イテレータに対応			//
//														//
//				Programmed By Akira.T					//
//		Copyright(C) 2006 Akira.T All rights reserved	//
//														//
//------------------------------------------------------//


#ifndef	SHAND_VECTOR_INCLUDE
#define SHAND_VECTOR_INCLUDE

#pragma warning(disable : 4530)
#include <vector>
#pragma warning(default : 4530)

#ifdef __AFX_H__
#include <afxtempl.h>	// CArray
#endif	// __AFX_H__

namespace shand {

template<class Type>
class CVector {
protected:
	std::vector<Type> m_arElement;	// 全要素

public:
	typedef typename std::vector<Type>::iterator		iterator;
	typedef typename std::vector<Type>::const_iterator	const_iterator;
	typedef Type&										reference;
	typedef Type										difference_type;
	typedef Type										value_type;

	// constructor
	CVector()
	{
		// 要素クリア
		RemoveAll();
	}

	CVector(const std::vector<Type> &arElement)
		: m_arElement(arElement)
	{
	}

#ifdef __AFX_H__
	CVector(const CArray<Type, Type&> &arElement)
	{
		m_arElement = arElement;
	}
#endif	// __AFX_H__

	virtual ~CVector() {}

	// operators
	CVector<Type>& operator=(const std::vector<Type> &arElement)
	{
		m_arElement = arElement;
		return *this;
	}

#ifdef __AFX_H__
	// MFC::CArrayクラスからの代入
	CVector<Type>& operator=(const CArray<Type, Type&> &arElement)
	{
		RemoveAll();
		for (int nIdx = 0; nIdx < arElement.GetSize(); nIdx++)
			Add(arElement[nIdx]);
			
		return *this;
	}
#endif	// __AFX_H__

	// cast
	operator std::vector<Type>()
	{
		return m_arElement;
	}

	// std::vectorへの変換
	const std::vector<Type>& c_vector() const
	{
		return m_arElement;
	}

	//--------------------------------------//
	// 名称 : RemoveAll()					//
	// 用途 : 全要素削除					//
	// 引数 : なし							//
	// 戻値 : なし							//
	//--------------------------------------//
	void RemoveAll()
	{
		m_arElement.clear();
	}


	//--------------------------------------//
	// 名称 : RemoveAt()					//
	// 用途 : 指定インデックス位置の要素削除//
	// 引数 : インデックス位置				//
	// 戻値 : なし							//
	//--------------------------------------//
	void RemoveAt(const int nIdx)
	{
		m_arElement.erase(m_arElement.begin() + nIdx);
	}


	//--------------------------------------//
	// 名称 : Add()							//
	// 用途 : 要素追加						//
	// 引数 : 追加する要素					//
	// 戻値 : なし							//
	//--------------------------------------//
	void Add(const Type& Element)
	{
		m_arElement.push_back(Element);
	}


	//--------------------------------------//
	// 名称 : Append()						//
	// 用途 : 要素追加						//
	// 引数 : 追加する要素					//
	// 戻値 : なし							//
	//--------------------------------------//
	void Append(const Type& Element)
	{
		m_arElement.push_back(Element);
	}


	//--------------------------------------//
	// 名称 : GetSize()						//
	// 用途 : 要素数取得					//
	// 引数 : なし							//
	// 戻値 : 要素数						//
	//--------------------------------------//
	int GetSize() const
	{
		return static_cast<int>(m_arElement.size());
	}


	//--------------------------------------//
	// 名称 : GetCount()					//
	// 用途 : 要素数取得					//
	// 引数 : なし							//
	// 戻値 : 要素数						//
	//--------------------------------------//
	int GetCount() const
	{
		return m_arElement.size();
	}


	//--------------------------------------//
	// 名称 : GetUpperBound()				//
	// 用途 : 有効なインデックスの最大値取得//
	// 引数 : なし							//
	// 戻値 : インデックス値(-1は不正)		//
	//--------------------------------------//
	int GetUpperBound() const
	{
		return m_arElement.size() -1;
	}


	//--------------------------------------//
	// 名称 : IsEmpty()						//
	// 用途 : 要素が空か判断				//
	// 引数 : なし							//
	// 戻値 : true:要素なし false:要素あり	//
	//--------------------------------------//
	bool IsEmpty() const
	{
		return m_arElement.size() <= 0;
	}


	//--------------------------------------//
	// 名称 : InsertAt()					//
	// 用途 : 要素の挿入					//
	// 引数 : nIdx		: インデックス位置	//
	//		  Element	: 新要素			//
	// 戻値 : なし							//
	//--------------------------------------//
	void InsertAt(const int nIdx, const Type& Element)
	{
		m_arElement.insert(m_arElement.begin() + nIdx, Element);
	}


	//--------------------------------------//
	// 名称 : SetAt()						//
	// 用途 : 要素の設定					//
	// 引数 : nIdx		: インデックス位置	//
	//		  Element	: 新要素			//
	// 戻値 : なし							//
	//--------------------------------------//
	void SetAt(const int nIdx, const Type& Element)
	{
		m_arElement[nIdx] = Element;
	}


	//--------------------------------------//
	// 名称 : SetSize()						//
	// 用途 : 要素数の再設定				//
	// 引数 : 新要素数						//
	// 戻値 : なし							//
	//--------------------------------------//
	void SetSize(const int nSize)
	{
		m_arElement.resize(nSize);
	}


	//--------------------------------------//
	// 名称 : ElementAt()					//
	// 用途 : 指定インデックス位置の要素取得//
	// 引数 : インデックス値				//
	// 戻値 : インデックス位置の要素		//
	//--------------------------------------//
	Type& ElementAt(const int nIdx)
	{
		return m_arElement[nIdx];
	}


	//--------------------------------------//
	// 名称 : GetAt()						//
	// 用途 : 指定インデックス位置の要素取得//
	// 引数 : インデックス値				//
	// 戻値 : インデックス位置の要素		//
	//--------------------------------------//
	Type& GetAt(const int nIdx)
	{
		return m_arElement[nIdx];
	}

	const Type& GetAt(const int nIdx) const
	{
		return m_arElement[nIdx];
	}


	//--------------------------------------//
	// [ ] 指定インデックス位置の要素取得	//
	//--------------------------------------//
	Type& operator[](const int nIdx)
	{
		return m_arElement[nIdx];
	}

	const Type& operator[](const int nIdx) const
	{
		return m_arElement[nIdx];
	}


	//--------------------------------------//
	// 名称 : begin()						//
	// 用途 : 先頭要素へのイテレータ取得	//
	// 引数 : なし							//
	// 戻値 : 先頭要素イテレータ			//
	//--------------------------------------//
	iterator begin()
	{
		return m_arElement.begin();
	}

	const_iterator begin() const
	{
		return m_arElement.begin();
	}


	//--------------------------------------//
	// 名称 : end()							//
	// 用途 : 最後尾要素へのイテレータ取得	//
	// 引数 : なし							//
	// 戻値 : 最後尾要素へのイテレータ		//
	//--------------------------------------//
	iterator end()
	{
		return m_arElement.end();
	}

	const_iterator end() const
	{
		return m_arElement.end();
	}

};

}	// namespace shand

#endif	// SHAND_VECTOR_INCLUDE

