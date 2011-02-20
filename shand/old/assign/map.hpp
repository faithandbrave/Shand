#ifndef SHAND_ASSIGN_MAP_INCLUDE
#define SHAND_ASSIGN_MAP_INCLUDE

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

