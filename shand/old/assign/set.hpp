#ifndef SHAND_ASSIGN_SET_INCLUDE
#define SHAND_ASSIGN_SET_INCLUDE

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

