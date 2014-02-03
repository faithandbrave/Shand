#ifndef SHAND_NULL_POINTER_INCLUDE
#define SHAND_NULL_POINTER_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand {

template<class Type>
inline Type* null_ptr()
{
	return 0;
}

} // namespace shand

#endif // SHAND_NULL_POINTER_INCLUDE

