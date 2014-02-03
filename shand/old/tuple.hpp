#ifndef SHAND_TUPLE_INCLUDE
#define SHAND_TUPLE_INCLUDE

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//------------------------------------------------------//
// Name : tuple											//
// Desc : 多重代入クラス								//
// Note : boost::tuples::tupleが元ネタ					//
//														//
// Version : 1.00 2006/10/19 作成						//
//														//
//------------------------------------------------------//

namespace shand
{

struct null_type {};

template<
	typename T0 = null_type, typename T1 = null_type, typename T2 = null_type,
	typename T3 = null_type, typename T4 = null_type, typename T5 = null_type,
	typename T6 = null_type, typename T7 = null_type, typename T8 = null_type,
	typename T9 = null_type
>
class tuple {
public:
	T0 t0;
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	T5 t5;
	T6 t6;
	T8 t8;
	T7 t7;
	T9 t9;

public:
	// constructors
	tuple(const T0 &u0 = T0(), const T1 &u1 = T1(), const T2 &u2 = T2(),
		  const T3 &u3 = T3(), const T4 &u4 = T4(), const T5 &u5 = T5(),
		  const T6 &u6 = T6(), const T7 &u7 = T7(), const T8 &u8 = T8(),
		  const T9 &u9 = T9())
		: t0(u0), t1(u1), t2(u2), t3(u3), t4(u4),
		  t5(u5), t6(u6), t7(u7), t8(u8), t9(u9)
	{
	}

	template<
		typename U0, typename U1, typename U2,
		typename U3, typename U4, typename U5,
		typename U6, typename U7, typename U8,
		typename U9
	>
	tuple(const tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &other)
		: t0(other.t0), t1(other.t1), t2(other.t2), t3(other.t3), t4(other.t4),
		  t5(other.t5), t6(other.t6), t7(other.t7), t8(other.t8), t9(other.t9)
	{
	}

	// operators
	template<
		typename U0, typename U1, typename U2,
		typename U3, typename U4, typename U5,
		typename U6, typename U7, typename U8,
		typename U9
	>
	tuple& operator = (const tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &other)
	{
		t0 = other.t0;
		t1 = other.t1;
		t2 = other.t2;
		t3 = other.t3;
		t4 = other.t4;
		t5 = other.t5;
		t6 = other.t6;
		t7 = other.t7;
		t8 = other.t8;
		t9 = other.t9;
		return *this;
	}

};



template<typename T0>
inline tuple<T0> make_tuple(const T0 &t0)
{
	return tuple<T0>(t0);
}

template<typename T0, typename T1>
inline tuple<T0, T1> make_tuple(const T0 &t0, const T1 &t1)
{
	return tuple<T0, T1>(t0, t1);
}

template<typename T0, typename T1, typename T2>
inline tuple<T0, T1, T2>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2)
{
	return tuple<T0, T1, T2>(t0, t1, t2);
}


template<typename T0, typename T1, typename T2,
		 typename T3>
inline tuple<T0, T1, T2, T3>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3)
{
	return tuple<T0, T1, T2, T3>
				(t0, t1, t2, t3);
}

template<typename T0, typename T1, typename T2,
		 typename T3, typename T4>
inline tuple<T0, T1, T2, T3, T4>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4)
{
	return tuple<T0, T1, T2, T3, T4>
				(t0, t1, t2, t3, t4);
}


template<typename T0, typename T1, typename T2,
		 typename T3, typename T4, typename T5>
inline tuple<T0, T1, T2, T3, T4, T5>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4, const T5 &t5)
{
	return tuple<T0, T1, T2, T3, T4, T5>
				(t0, t1, t2, t3, t4, t5);
}

template<typename T0, typename T1, typename T2,
		 typename T3, typename T4, typename T5,
		 typename T6>
inline tuple<T0, T1, T2, T3, T4, T5, T6>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4, const T5 &t5,
		   const T6 &t6)
{
	return tuple<T0, T1, T2, T3, T4, T5, T6>
				(t0, t1, t2, t3, t4, t5, t6);
}


template<typename T0, typename T1, typename T2,
		 typename T3, typename T4, typename T5,
		 typename T6, typename T7>
inline tuple<T0, T1, T2, T3, T4, T5, T6, T7>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4, const T5 &t5,
		   const T6 &t6, const T7 &t7)
{
	return tuple<T0, T1, T2, T3, T4, T5, T6, T7>
				(t0, t1, t2, t3, t4, t5, t6, t7);
}


template<typename T0, typename T1, typename T2,
		 typename T3, typename T4, typename T5,
		 typename T6, typename T7, typename T8>
inline tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4, const T5 &t5,
		   const T6 &t6, const T7 &t7, const T8 &t8)
{
	return tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
				(t0, t1, t2, t3, t4, t5, t6, t7, t8);
}


template<typename T0, typename T1, typename T2,
		 typename T3, typename T4, typename T5,
		 typename T6, typename T7, typename T8,
		 typename T9>
inline tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
make_tuple(const T0 &t0, const T1 &t1, const T2 &t2,
		   const T3 &t3, const T4 &t4, const T5 &t5,
		   const T6 &t6, const T7 &t7, const T8 &t8,
		   const T9 &t9)
{
	return tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
				(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

} // namespace shand

#endif	// SHAND_TUPLE_INCLUDE


/*------------------------------------------------------|
|					How to use							|
|-------------------------------------------------------|
|---[tuple get function]--------------------------------|
|														|
| tuple<int, string> get_info()							|
| {														|
|    return make_tuple(3, string("abc"));				|
| }														|
|														|
|---[tuple get and show]--------------------------------|
|														|
| tuple<int, string> tup = get_info();					|
|														|
| cout << tup.t0 << endl; // int						|
| cout << tup.t1 << endl; // string						|
|														|
|---[execution result]----------------------------------|
|														|
|	|---------------------------|						|
|	| 3							|						|
|	| abc						|						|
|	|							|						|
|	|---------------------------|						|
|------------------------------------------------------*/

