#ifndef SHAND_LEXICAL_CAST_INCLUDE
#define SHAND_LEXICAL_CAST_INCLUDE

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

