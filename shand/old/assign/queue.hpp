#ifndef SHAND_ASSIGN_QUEUE_INCLUDE
#define SHAND_ASSIGN_QUEUE_INCLUDE

// Copyright Thorsten Ottosen 2003-2004.
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <queue>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Type>
inline list_inserter<assign_detail::call_push<std::queue<Type> > >
operator+=(std::queue<Type>& container, Type value)
{
	return push(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_QUEUE_INCLUDE

