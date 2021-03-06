#ifndef SHAND_ASSIGN_MAP_INCLUDE
#define SHAND_ASSIGN_MAP_INCLUDE

// Copyright Thorsten Ottosen 2003-2004.
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Key, class Type, class Pair>
inline list_inserter<assign_detail::call_insert<std::map<Key, Type> > >
operator+=(std::map<Key, Type>& container, Pair value)
{
	return insert(container)(value);
}

template <class Key, class Type, class Pair>
inline list_inserter<assign_detail::call_insert<std::multimap<Key, Type> > >
operator+=(std::multimap<Key, Type>& container, Pair value)
{
	return insert(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_MAP_INCLUDE

