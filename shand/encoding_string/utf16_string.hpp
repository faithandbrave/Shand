#ifndef SHAND_ENCODING_STRING_UTF16_INCLUDE
#define SHAND_ENCODING_STRING_UTF16_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/config.hpp>

namespace shand {

template <>
class encoding_string<encoding::utf16> {
public:
#if defined(BOOST_NO_CXX11_CHAR16_T)
	using cchar_type = wchar_t;
#else
	using cchar_type = char16_t;
#endif
    using string_type = std::basic_string<cchar_type>;
    using value_type = std::basic_string<cchar_type>;

    encoding_string(const cchar_type* s)
        : data_(s) {}

	const cchar_type* c_str() const
	{ return data_.c_str(); }

private:
    string_type data_;
};

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF16_INCLUDE

