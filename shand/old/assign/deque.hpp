#ifndef SHAND_ASSIGN_DEQUE_INCLUDE
#define SHAND_ASSIGN_DEQUE_INCLUDE

#include <deque>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Type>
inline list_inserter<assign_detail::call_push_back<std::deque<Type> > >
operator+=(std::deque<Type>& container, Type value)
{
	return push_back(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_DEQUE_INCLUDE

