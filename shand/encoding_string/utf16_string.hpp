#ifndef SHAND_ENCODING_STRING_UTF16_INCLUDE
#define SHAND_ENCODING_STRING_UTF16_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <stdexcept>
#include <string>
#include <boost/config.hpp>
#include <boost/optional.hpp>
#include "./codeunit_iterator.hpp"

namespace shand {

namespace utf16_detail {

template <class CharT>
bool is_high_surrogate(const CharT& c)
{ return c >= static_cast<CharT>(0xD800) && c <= static_cast<CharT>(0xDBFF); }

template <class CharT>
bool is_low_surrogate(const CharT& c)
{ return c >= static_cast<CharT>(0xDC00) && c <= static_cast<CharT>(0xDFFF); }

template <class CharT>
bool is_surrogate_pair(const CharT& high, const CharT& low)
{ return is_high_surrogate(high) && is_low_surrogate(low); }

struct utf16_size_getter {
    template <class CharT>
    std::size_t operator()(const std::basic_string<CharT>& data, std::size_t i)
    {
        return (i < data.size() - 1 && is_surrogate_pair(data[i], data[i + 1])) ? 2 : 1;
    }
};

} // namespace utf16_detail

template <>
class encoding_string<encoding::utf16> {
public:
#if defined(BOOST_NO_CXX11_CHAR16_T)
    using cchar_type = wchar_t;
#else
    using cchar_type = char16_t;
#endif
    using string_type = std::basic_string<cchar_type>;
    using value_type = encoding_string<encoding::utf16>;
    using iterator = codeunit_iterator<string_type, value_type, utf16_detail::utf16_size_getter>;
    using const_iterator = iterator;

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

    encoding_string<encoding::utf16> codeunit_substr(std::size_t index, std::size_t codeunit_size) const
    {
        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = 0;

        boost::optional<std::size_t> start;
        while (i < size) {
            if (!start && len == index) {
                start = i;
            }
            const std::size_t n = char_size(i);
            i += n;
            ++len;
            if (!start)
                continue;

            --codeunit_size;
            if (codeunit_size == 0) {
                return data_.substr(start.get(), i).c_str();
            }
        }
        throw std::out_of_range("out of range");
    }

    encoding_string<encoding::utf16> codeunit_substr(std::size_t index) const
    {
        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = 0;

        while (i < size) {
            if (len == index) {
                return data_.substr(i).c_str();
            }
            i += char_size(i);
            ++len;
        }
        throw std::out_of_range("out of range");
    }

    iterator begin()
    { return iterator(data_); }

    const_iterator begin() const
    { return const_iterator(data_); }

    iterator end()
    { return iterator(); }

    const_iterator end() const
    { return const_iterator(); }

    const cchar_type* c_str() const
    { return data_.c_str(); }

    const string_type& raw_str() const
    { return data_; }

    bool empty() const
    { return data_.empty(); }

private:
    std::size_t char_size(std::size_t i) const
    { return utf16_detail::utf16_size_getter()(data_, i); }

    string_type data_;
};

inline bool operator==(const encoding_string<encoding::utf16>& a, const encoding_string<encoding::utf16>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::utf16>& a, const encoding_string<encoding::utf16>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF16_INCLUDE

