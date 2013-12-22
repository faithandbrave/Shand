#ifndef SHAND_ENCODING_STRING_UTF32_INCLUDE
#define SHAND_ENCODING_STRING_UTF32_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>

namespace shand {

template <>
class encoding_string<encoding::utf32> {
public:
#if defined(BOOST_NO_CXX11_CHAR32_T)
    using cchar_type = boost::uint32_t;
#else
    using cchar_type = char32_t;
#endif
    using string_type = std::basic_string<cchar_type>;
    using value_type = std::basic_string<cchar_type>;

    encoding_string() {}
    encoding_string(const cchar_type* s)
        : data_(s) {}

    const cchar_type* c_str() const
    { return data_.c_str(); }

    const string_type& raw_str() const
    { return data_; }

    bool empty() const
    { return data_.empty(); }

private:
    string_type data_;
};

inline bool operator==(const encoding_string<encoding::utf32>& a, const encoding_string<encoding::utf32>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::utf32>& a, const encoding_string<encoding::utf32>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF32_INCLUDE

