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

    encoding_string() {}
    encoding_string(const cchar_type* s)
        : data_(s) {}

    std::size_t codeunit_size() const
    {
        const std::size_t size = data_.size();
        std::size_t i = 0;
        std::size_t len = 0;
        while (i < size) {
            if (i < size - 1 && is_surrogate_pair(data_[i], data_[i + 1])) {
                ++i;
            }
            ++i;
            ++len;
        }
        return len;
    }

    const cchar_type* c_str() const
    { return data_.c_str(); }

    const string_type& raw_str() const
    { return data_; }

    bool empty() const
    { return data_.empty(); }

private:
    bool is_high_surrogate(const cchar_type& c) const
    { return c >= static_cast<cchar_type>(0xD800) && c <= static_cast<cchar_type>(0xDBFF); }

    bool is_low_surrogate(const cchar_type& c) const
    { return c >= static_cast<cchar_type>(0xDC00) && c <= static_cast<cchar_type>(0xDFFF); }

    bool is_surrogate_pair(const cchar_type& high, const cchar_type& low) const
    { return is_high_surrogate(high) && is_low_surrogate(low); }

    string_type data_;
};

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF16_INCLUDE

