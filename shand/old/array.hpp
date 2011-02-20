#ifndef	SHAND_ARRAY_INCLUDE
#define SHAND_ARRAY_INCLUDE

//----------------------------------------------------------//
// Name : array<Type, Size>									//
// Desc : �Œ蒷�z��N���X									//
// Note : �ʏ�̔z����Avector�̂悤�Ɏg����N���X			//
//			���l�^��boost::array							//
//															//
// Version : 1.00 2006/12/14 �쐬							//
//			 1.01 2007.05/15 reverse_iterator��VC6�ɑΉ�	//
//															//
//				Programmed By Akira.T						//
//		Copyright(C) 2006-2007 Akira.T All rights reserved	//
//															//
//----------------------------------------------------------//


#include <algorithm>

namespace shand {

template <class Type, size_t Size>
class array {
public:
	Type element_[Size];

public:
	typedef Type&                                       reference;
	typedef Type										difference_type;
	typedef Type										value_type;
	typedef Type*										iterator;
	typedef const Type*									const_iterator;

#if defined(_MSC_VER) && _MSC_VER <= 1201
	typedef std::reverse_iterator<iterator, Type>		reverse_iterator;
	typedef std::reverse_iterator<const_iterator, Type>	const_reverse_iterator;
#else
	typedef std::reverse_iterator<iterator>				reverse_iterator;
	typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
#endif

public:
	// �Y���ł̗v�f�Q��
	Type& operator[](int index)
	{
		return element_[index];
	}

	const Type& operator[](int index) const
	{
		return element_[index];
	}

	// �z��T�C�Y�擾
	int size() const { return Size;	}

	// �擪�v�f�ւ̃C�e���[�^�擾
	iterator		begin()			{ return element_; }
	const_iterator	begin() const	{ return element_; }

	// �Ō���v�f�ւ̃C�e���[�^�擾
	iterator		end()			{ return element_ + Size; }
	const_iterator	end() const		{ return element_ + Size; }

	reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }

	reverse_iterator		rend()			{ return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }
};

// ��r���Z�q
template <typename Type, size_t Size>
bool operator== (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type, size_t Size>
bool operator!= (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return !(lhs == rhs);
}

template <typename Type, size_t Size>
bool operator< (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type, size_t Size>
bool operator> (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return rhs < lhs;
}

template <typename Type, size_t Size>
bool operator<= (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return !(rhs < lhs);
}

template <typename Type, size_t Size>
bool operator>= (const shand::array<Type, Size> &lhs, const shand::array<Type, Size> &rhs)
{
	return !(lhs < rhs);
}

} // namespace shand

//==============================================================//
//						How to use								//
//==============================================================//
// array<int, 4> ar; // int�^4�̔z��쐬						//
//																//
// for (int i = 0; i < ar.size(); i++)	// �z��T�C�Y�̎擾��	//
//     ar[i] = i;	// �C���f�b�N�X�̎Q��						//
//																//
// // �C�e���[�^�ɂ��Q��										//
// for_each(ar.begin(), ar.end(), disp_function);				//
//																//
//==============================================================//
// // C����̔z��Ɠ��l�̏������q���X�g�ł̏��������\			//
// array<int, 3> ar = {3, 1, 4};								//
//																//
//==============================================================//

#endif	// SHAND_ARRAY_INCLUDE
