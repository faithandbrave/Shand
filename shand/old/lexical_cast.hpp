#ifndef SHAND_LEXICAL_CAST_INCLUDE
#define SHAND_LEXICAL_CAST_INCLUDE

// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <exception>
#include <sstream>
#include <string>

namespace shand {

class bad_lexical_cast : public std::bad_cast
{
public:
	bad_lexical_cast(const std::string& what)
		: std::bad_cast(what.c_str()) {}
};


template <class AfterType, class BeforeType>
AfterType lexical_cast(const BeforeType& target)
{
	AfterType			result;
	std::stringstream	interpreter;

	if (!(interpreter << target && interpreter >> result))
		throw bad_lexical_cast("bad_lexical_cast");

	return result;
}

template <class AfterType, class BeforeType>
AfterType wlexical_cast(const BeforeType& target)
{
	AfterType			result;
	std::wstringstream	interpreter;

	if (!(interpreter << target && interpreter >> result))
		throw bad_lexical_cast("bad_lexical_cast");

	return result;
}

} // namespace shand

#endif // SHAND_LEXICAL_CAST_INCLUDE

