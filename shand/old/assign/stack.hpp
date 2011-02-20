#ifndef SHAND_ASSIGN_STACK_INCLUDE
#define SHAND_ASSIGN_STACK_INCLUDE

#include <stack>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Type>
inline list_inserter<assign_detail::call_push<std::stack<Type> > >
operator+=(std::stack<Type>& container, Type value)
{
	return push(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_STACK_INCLUDE

