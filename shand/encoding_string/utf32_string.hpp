#ifndef SHAND_ENCODING_STRING_UTF32_INCLUDE
#define SHAND_ENCODING_STRING_UTF32_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include "./codeunit_iterator.hpp"

namespace shand {

namespace utf32_detail {

template <class String>
std::size_t ignore_bom(const String& data)
{
    if (data.size() < 1)
        return 0;

    // big endian
    if (data[0] == 0x0000feff)
        return 1;

    // little endian
    if (data[0] == 0xfffe0000)
        return 1;

    return 0;
}

struct bom_skipper {
    template <class String>
    std::size_t operator()(const String& data) const
    {
        return ignore_bom(data);
    }
};

struct size_getter {
    template <class String>
    std::size_t operator()(const String& data, std::size_t i) const
    {
        static_cast<void>(data);
        static_cast<void>(i);
        return 1;
    }
};

} // namespace utf32_detail

template <>
class encoding_string<encoding::utf32> {
public:
#if defined(BOOST_NO_CXX11_CHAR32_T)
    using cchar_type = boost::uint32_t;
#else
    using cchar_type = char32_t;
#endif
    using string_type = std::basic_string<cchar_type>;
    using value_type = encoding_string<encoding::utf32>;

    using iterator = codeunit_iterator<
                        string_type,
                        value_type,
                        utf32_detail::size_getter,
                        utf32_detail::bom_skipper>;
    using const_iterator = iterator;

    encoding_string() {}
    encoding_string(const cchar_type* s)
        : data_(s) {}

    std::size_t codeunit_size() const
    { return data_.size() - utf32_detail::ignore_bom(data_); }

    encoding_string<encoding::utf32> codeunit_at(std::size_t index) const
    { return string_type(1, data_.at(index + utf32_detail::ignore_bom(data_))).c_str(); }

    std::uint32_t codeunit_value_at(std::size_t index) const
    { return static_cast<std::uint32_t>(data_.at(index + utf32_detail::ignore_bom(data_))); }

    encoding_string<encoding::utf32> codeunit_substr(std::size_t index, std::size_t codeunit_size) const
    { return data_.substr(index + utf32_detail::ignore_bom(data_), codeunit_size).c_str(); }

    encoding_string<encoding::utf32> codeunit_substr(std::size_t index) const
    { return data_.substr(index + utf32_detail::ignore_bom(data_)).c_str(); }

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
    string_type data_;
};

inline bool operator==(const encoding_string<encoding::utf32>& a, const encoding_string<encoding::utf32>& b)
{ return a.raw_str() == b.raw_str(); }

inline bool operator!=(const encoding_string<encoding::utf32>& a, const encoding_string<encoding::utf32>& b)
{ return !(a == b); }

} // namespace shand

#endif // SHAND_ENCODING_STRING_UTF32_INCLUDE

