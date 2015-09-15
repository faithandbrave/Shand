#ifndef SHAND_ENCODING_STRING_UTF8_INCLUDE
#define SHAND_ENCODING_STRING_UTF8_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <string>
#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/utility/string_ref.hpp>
#include "./codeunit_iterator.hpp"

namespace shand {

namespace utf8_detail {

inline const char* length_table()
{
    static const char table[256] = {
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1,
    };
    return table;
}

std::size_t ignore_bom(const std::basic_string<char>& data)
{
    if (data.size() < 3)
        return 0;

    if (static_cast<unsigned char>(data[0]) == 0xef &&
        static_cast<unsigned char>(data[1]) == 0xbb &&
        static_cast<unsigned char>(data[2]) == 0xbf)
        return 3;

    return 0;
}

struct bom_skipper {
    std::size_t operator()(const std::basic_string<char>& data) const
    {
        return ignore_bom(data);
    }
};

struct size_getter {
    std::size_t operator()(const std::basic_string<char>& data, std::size_t i) const
    {
        const unsigned char c = data[i];
        const std::size_t size = length_table()[c];
        return size;
    }
};

} // namespace utf8_detail

template <>
class encoding_string<encoding::utf8> {
public:
    using string_type = std::basic_string<char>;
    using value_type = encoding_string<encoding::utf8>;
    using cchar_type = char;
    using iterator = codeunit_iterator<
                        string_type,
                        value_type,
                        utf8_detail::size_getter,
                        utf8_detail::bom_skipper>;
    using const_iterator = iterator;

    encoding_string() {}
    encoding_string(const char* s)
        : data_(s) {}

    std::size_t codeunit_size() const
    {
        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = utf8_detail::ignore_bom(data_);
        while (i < size) {
            i += char_size(i);
            ++len;
        }
        return len;
    }

    // O(N)
    value_type codeunit_at(std::size_t index) const
    {
        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = utf8_detail::ignore_bom(data_);
        while (i < size) {
            const std::size_t n = char_size(i);
            if (len == index) {
                return string_type(data_, i, n).c_str();
            }
            i += n;
            ++len;
        }
        throw std::out_of_range("out of range");
    }

    std::uint32_t codeunit_value_at(std::size_t index) const
    {
        const value_type codeunit = codeunit_at(index);
        const string_type s = codeunit.raw_str();
        const std::size_t size = s.size();
        if (size == 1) {
            const std::uint32_t c0 = static_cast<std::uint32_t>(s[0]);
            return c0;
        }
        if (size == 2) {
            const std::uint32_t c0 = static_cast<std::uint32_t>(s[0]);
            const std::uint32_t c1 = static_cast<std::uint32_t>(s[1]);
            return ((c0 & 0x1F) << 6) | (c1 & 0x3F);
        }
        if (size == 3) {
            const std::uint32_t c0 = static_cast<std::uint32_t>(s[0]);
            const std::uint32_t c1 = static_cast<std::uint32_t>(s[1]);
            const std::uint32_t c2 = static_cast<std::uint32_t>(s[2]);
            return ((c0 & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
        }
        if (size == 4) {
            const std::uint32_t c0 = static_cast<std::uint32_t>(s[0]);
            const std::uint32_t c1 = static_cast<std::uint32_t>(s[1]);
            const std::uint32_t c2 = static_cast<std::uint32_t>(s[2]);
            const std::uint32_t c3 = static_cast<std::uint32_t>(s[3]);
            return (c0 << 16) | ((c1 & 0x0F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
        }
        throw std::out_of_range("out of range");
    }

    encoding_string<encoding::utf8> codeunit_substr(std::size_t index, std::size_t codeunit_size) const
    {
        assert(codeunit_size > 0);

        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = utf8_detail::ignore_bom(data_);

        boost::optional<std::size_t> start;
        while (i < size) {
            if (!start && len == index) {
                start = i;
            }

            if (len == index + codeunit_size) {
                return data_.substr(start.get(), i - start.get()).c_str();
            }

            const std::size_t n = char_size(i);
            ++len;
            i += n;
        }
        throw std::out_of_range("out of range");
    }

    encoding_string<encoding::utf8> codeunit_substr(std::size_t index) const
    {
        const std::size_t size = data_.size();
        std::size_t len = 0;
        std::size_t i = utf8_detail::ignore_bom(data_);

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
    std::size_t char_size(std::size_t index) const
    {
        const unsigned char c = data_[index];
        return utf8_detail::length_table()[c];
    }

    string_type data_;
};

inline bool operator==(const encoding_string<encoding::utf8>& a, const encoding_string<encoding::utf8>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::utf8>& a, const encoding_string<encoding::utf8>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF8_INCLUDE

