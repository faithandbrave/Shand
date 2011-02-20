#ifndef SHAND_TO_CSTRING_INCLUDE
#define SHAND_TO_CSTRING_INCLUDE

#include <shand/string_algorithm.hpp>

template <class Type>
inline CString ToString(const Type& value)
{
#ifdef _UNICODE
	return shand::to_wstring(value).c_str();
#else
	return shand::to_string(value).c_str();
#endif // _UNICODE

}


#endif // SHAND_TO_CSTRING_INCLUDE

