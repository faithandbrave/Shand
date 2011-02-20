#ifndef SHAND_ASSIGN_QUEUE_INCLUDE
#define SHAND_ASSIGN_QUEUE_INCLUDE

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

