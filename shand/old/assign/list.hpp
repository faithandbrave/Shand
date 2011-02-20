#ifndef SHAND_ASSIGN_LIST_INCLUDE
#define SHAND_ASSIGN_LIST_INCLUDE

#include <list>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Type>
inline list_inserter<assign_detail::call_push_back<std::list<Type> > >
operator+=(std::list<Type>& container, Type value)
{
	return push_back(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_LIST_INCLUDE

