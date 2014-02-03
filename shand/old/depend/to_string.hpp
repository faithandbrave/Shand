// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef SHAND_TO_CSTRING_INCLUDE
#define SHAND_TO_CSTRING_INCLUDE

#include <shand/string_algorithm.hpp>

template <class Type>
inline CString ToString(const Type& value)
{
#ifdef _UNICODE
	return shand::to_wstring(value).c_str();
#else
	return shand::to_string(value).c_str();
#endif // _UNICODE

}


#endif // SHAND_TO_CSTRING_INCLUDE

