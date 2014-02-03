#ifndef SHAND_ASSIGN_SET_INCLUDE
#define SHAND_ASSIGN_SET_INCLUDE

// Copyright Thorsten Ottosen 2003-2004.
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <set>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Key, class Type>
inline list_inserter<assign_detail::call_insert<std::set<Key> > >
operator+=(std::set<Key>& container, Type value)
{
	return insert(container)(value);
}

template <class Key, class Type>
inline list_inserter<assign_detail::call_insert<std::multiset<Key> > >
operator+=(std::multiset<Key>& container, Type value)
{
	return insert(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_SET_INCLUDE

