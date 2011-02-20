#ifndef SHAND_ASSIGN_VECTOR_INCLUDE
#define SHAND_ASSIGN_VECTOR_INCLUDE

#include <vector>
#include "list_inserter.hpp"

namespace shand { namespace assign {

template <class Type>
inline list_inserter<assign_detail::call_push_back<std::vector<Type> > >
operator+=(std::vector<Type>& container, Type value)
{
	return push_back(container)(value);
}

}} // namespace shand::assign

#endif // SHAND_ASSIGN_VECTOR_INCLUDE

