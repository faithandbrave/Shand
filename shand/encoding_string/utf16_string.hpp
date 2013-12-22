#ifndef SHAND_ENCODING_STRING_UTF16_INCLUDE
#define SHAND_ENCODING_STRING_UTF16_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <stdexcept>
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
            i += char_size(i);
            ++len;
        }
        return len;
    }

    // O(N)
    encoding_string<encoding::utf16> codeunit_at(std::size_t index) const
    {
        const std::size_t size = data_.size();
        std::size_t i = 0;
        std::size_t len = 0;
        while (i < size) {
            const std::size_t n = char_size(i);
            if (len == index) {
                return data_.substr(i, n).c_str();
            }
            i += n;
            ++len;
        }
        throw std::out_of_range("out of range");
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

    std::size_t char_size(std::size_t i) const
    { return (i < data_.size() - 1 && is_surrogate_pair(data_[i], data_[i + 1])) ? 2 : 1; }

    string_type data_;
};

inline bool operator==(const encoding_string<encoding::utf16>& a, const encoding_string<encoding::utf16>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::utf16>& a, const encoding_string<encoding::utf16>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF16_INCLUDE

