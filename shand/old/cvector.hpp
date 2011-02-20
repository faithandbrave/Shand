//------------------------------------------------------//
// Name : CVector<Type>									//
// Desc : �ϒ��z��N���X								//
// Note : std::vector���AMFC��CArray���Ƀ��b�v�����N���X//
//														//
// Version : 1.00 2006/09/20 �쐬						//
// Version : 1.01 2006/11/10 �C�e���[�^�ɑΉ�			//
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
	std::vector<Type> m_arElement;	// �S�v�f

public:
	typedef typename std::vector<Type>::iterator		iterator;
	typedef typename std::vector<Type>::const_iterator	const_iterator;
	typedef Type&										reference;
	typedef Type										difference_type;
	typedef Type										value_type;

	// constructor
	CVector()
	{
		// �v�f�N���A
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
	// MFC::CArray�N���X����̑��
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

	// std::vector�ւ̕ϊ�
	const std::vector<Type>& c_vector() const
	{
		return m_arElement;
	}

	//--------------------------------------//
	// ���� : RemoveAll()					//
	// �p�r : �S�v�f�폜					//
	// ���� : �Ȃ�							//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void RemoveAll()
	{
		m_arElement.clear();
	}


	//--------------------------------------//
	// ���� : RemoveAt()					//
	// �p�r : �w��C���f�b�N�X�ʒu�̗v�f�폜//
	// ���� : �C���f�b�N�X�ʒu				//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void RemoveAt(const int nIdx)
	{
		m_arElement.erase(m_arElement.begin() + nIdx);
	}


	//--------------------------------------//
	// ���� : Add()							//
	// �p�r : �v�f�ǉ�						//
	// ���� : �ǉ�����v�f					//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void Add(const Type& Element)
	{
		m_arElement.push_back(Element);
	}


	//--------------------------------------//
	// ���� : Append()						//
	// �p�r : �v�f�ǉ�						//
	// ���� : �ǉ�����v�f					//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void Append(const Type& Element)
	{
		m_arElement.push_back(Element);
	}


	//--------------------------------------//
	// ���� : GetSize()						//
	// �p�r : �v�f���擾					//
	// ���� : �Ȃ�							//
	// �ߒl : �v�f��						//
	//--------------------------------------//
	int GetSize() const
	{
		return static_cast<int>(m_arElement.size());
	}


	//--------------------------------------//
	// ���� : GetCount()					//
	// �p�r : �v�f���擾					//
	// ���� : �Ȃ�							//
	// �ߒl : �v�f��						//
	//--------------------------------------//
	int GetCount() const
	{
		return m_arElement.size();
	}


	//--------------------------------------//
	// ���� : GetUpperBound()				//
	// �p�r : �L���ȃC���f�b�N�X�̍ő�l�擾//
	// ���� : �Ȃ�							//
	// �ߒl : �C���f�b�N�X�l(-1�͕s��)		//
	//--------------------------------------//
	int GetUpperBound() const
	{
		return m_arElement.size() -1;
	}


	//--------------------------------------//
	// ���� : IsEmpty()						//
	// �p�r : �v�f���󂩔��f				//
	// ���� : �Ȃ�							//
	// �ߒl : true:�v�f�Ȃ� false:�v�f����	//
	//--------------------------------------//
	bool IsEmpty() const
	{
		return m_arElement.size() <= 0;
	}


	//--------------------------------------//
	// ���� : InsertAt()					//
	// �p�r : �v�f�̑}��					//
	// ���� : nIdx		: �C���f�b�N�X�ʒu	//
	//		  Element	: �V�v�f			//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void InsertAt(const int nIdx, const Type& Element)
	{
		m_arElement.insert(m_arElement.begin() + nIdx, Element);
	}


	//--------------------------------------//
	// ���� : SetAt()						//
	// �p�r : �v�f�̐ݒ�					//
	// ���� : nIdx		: �C���f�b�N�X�ʒu	//
	//		  Element	: �V�v�f			//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void SetAt(const int nIdx, const Type& Element)
	{
		m_arElement[nIdx] = Element;
	}


	//--------------------------------------//
	// ���� : SetSize()						//
	// �p�r : �v�f���̍Đݒ�				//
	// ���� : �V�v�f��						//
	// �ߒl : �Ȃ�							//
	//--------------------------------------//
	void SetSize(const int nSize)
	{
		m_arElement.resize(nSize);
	}


	//--------------------------------------//
	// ���� : ElementAt()					//
	// �p�r : �w��C���f�b�N�X�ʒu�̗v�f�擾//
	// ���� : �C���f�b�N�X�l				//
	// �ߒl : �C���f�b�N�X�ʒu�̗v�f		//
	//--------------------------------------//
	Type& ElementAt(const int nIdx)
	{
		return m_arElement[nIdx];
	}


	//--------------------------------------//
	// ���� : GetAt()						//
	// �p�r : �w��C���f�b�N�X�ʒu�̗v�f�擾//
	// ���� : �C���f�b�N�X�l				//
	// �ߒl : �C���f�b�N�X�ʒu�̗v�f		//
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
	// [ ] �w��C���f�b�N�X�ʒu�̗v�f�擾	//
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
	// ���� : begin()						//
	// �p�r : �擪�v�f�ւ̃C�e���[�^�擾	//
	// ���� : �Ȃ�							//
	// �ߒl : �擪�v�f�C�e���[�^			//
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
	// ���� : end()							//
	// �p�r : �Ō���v�f�ւ̃C�e���[�^�擾	//
	// ���� : �Ȃ�							//
	// �ߒl : �Ō���v�f�ւ̃C�e���[�^		//
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

