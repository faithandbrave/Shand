#ifndef	SHAND_ARRAY_INCLUDE
#define SHAND_ARRAY_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// The original author site is at: http://www.josuttis.com/
//
// (C) Copyright Nicolai M. Josuttis 2001.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------//
// Name : array<Type, Size>									//
// Desc : 固定長配列クラス									//
// Note : 通常の配列を、vectorのように使えるクラス			//
//			元ネタはboost::array							//
//															//
// Version : 1.00 2006/12/14 作成							//
//			 1.01 2007.05/15 reverse_iteratorをVC6に対応	//
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
	// 添字での要素参照
	Type& operator[](int index)
	{
		return element_[index];
	}

	const Type& operator[](int index) const
	{
		return element_[index];
	}

	// 配列サイズ取得
	int size() const { return Size;	}

	// 先頭要素へのイテレータ取得
	iterator		begin()			{ return element_; }
	const_iterator	begin() const	{ return element_; }

	// 最後尾要素へのイテレータ取得
	iterator		end()			{ return element_ + Size; }
	const_iterator	end() const		{ return element_ + Size; }

	reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }

	reverse_iterator		rend()			{ return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }
};

// 比較演算子
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
// array<int, 4> ar; // int型4つの配列作成						//
//																//
// for (int i = 0; i < ar.size(); i++)	// 配列サイズの取得可	//
//     ar[i] = i;	// インデックスの参照						//
//																//
// // イテレータによる参照										//
// for_each(ar.begin(), ar.end(), disp_function);				//
//																//
//==============================================================//
// // C言語の配列と同様の初期化子リストでの初期化が可能			//
// array<int, 3> ar = {3, 1, 4};								//
//																//
//==============================================================//

#endif	// SHAND_ARRAY_INCLUDE
