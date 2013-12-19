#ifndef SHAND_ENCODING_STRING_SYSTEM_INCLUDE
#define SHAND_ENCODING_STRING_SYSTEM_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace shand {

template <>
class encoding_string<encoding::system> {
public:
    using string_type = std::basic_string<char>;
    using value_type = std::basic_string<char>;
    using cchar_type = char;

    encoding_string() {}
    encoding_string(const char* s)
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

inline bool operator==(const encoding_string<encoding::system>& a, const encoding_string<encoding::system>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::system>& a, const encoding_string<encoding::system>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_SYSTEM_INCLUDE

