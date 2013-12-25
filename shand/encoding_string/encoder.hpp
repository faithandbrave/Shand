#ifndef SHAND_ENCODING_STRING_ENCODER_INCLUDE
#define SHAND_ENCODING_STRING_ENCODER_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <stdexcept>
#include <boost/predef.h>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "./utf16_string.hpp"
#include "./utf8_string.hpp"
#include "./system_string.hpp"

#if BOOST_OS_WINDOWS
#include <Windows.h>
#endif

/* implementation status

vertical   : from
horizontal : to

|        | 8  | 16 | 32 | system |
| 8      | -  | OK | OK | OK     |
| 16     | OK | -  | OK | OK     |
| 32     | OK | OK | -  | OK     |
| system | NO | NO | NO | -      |

*/

namespace shand {

template <class From, class To>
class encoder;

namespace encode_detail {

template <class To, template <class, class> class Iterator, class From>
encoding_string<To> boost_encode(const encoding_string<From>& from)
{
    if (from.empty())
        return {};

    using from_raw_string_type = typename encoding_string<From>::string_type;
    using conversion_iterator = Iterator<
        typename from_raw_string_type::const_iterator,
        typename encoding_string<To>::cchar_type
    >;

    conversion_iterator first(from.raw_str().begin());
    conversion_iterator last(from.raw_str().end());

    typename encoding_string<To>::string_type result;
    for (; first != last; ++first) {
        result.push_back(*first);
    }
    return result.c_str();
}

} // namespace encode_detail

template <class Encoding>
class encoder<Encoding, Encoding> {
public:
    static encoding_string<Encoding> encode(const encoding_string<Encoding>& s)
    {
        return s;
    }
};

template <>
class encoder<encoding::utf8, encoding::utf32> {
public:
    static encoding_string<encoding::utf32> encode(const encoding_string<encoding::utf8>& utf8)
    {
        return encode_detail::boost_encode<encoding::utf32, boost::u8_to_u32_iterator>(utf8);
    }
};

template <>
class encoder<encoding::utf16, encoding::utf32> {
public:
    static encoding_string<encoding::utf32> encode(const encoding_string<encoding::utf16>& utf16)
    {
        return encode_detail::boost_encode<encoding::utf32, boost::u16_to_u32_iterator>(utf16);
    }
};

template <>
class encoder<encoding::utf32, encoding::utf8> {
public:
    static encoding_string<encoding::utf8> encode(const encoding_string<encoding::utf32>& utf32)
    {
        return encode_detail::boost_encode<encoding::utf8, boost::u32_to_u8_iterator>(utf32);
    }
};

template <>
class encoder<encoding::utf32, encoding::utf16> {
public:
    static encoding_string<encoding::utf16> encode(const encoding_string<encoding::utf32>& utf32)
    {
        return encode_detail::boost_encode<encoding::utf16, boost::u32_to_u16_iterator>(utf32);
    }
};

template <>
class encoder<encoding::utf8, encoding::utf16> {
public:
    static encoding_string<encoding::utf16> encode(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return {};

        const encoding_string<encoding::utf32> utf32 = encoder<
            encoding::utf8,
            encoding::utf32
        >::encode(utf8);

        const encoding_string<encoding::utf16> utf16 = encoder<
            encoding::utf32,
            encoding::utf16
        >::encode(utf32);

        return utf16.c_str();
    }
};

template <>
class encoder<encoding::utf16, encoding::utf8> {
public:
    static encoding_string<encoding::utf8> encode(const encoding_string<encoding::utf16>& utf16)
    {
        if (utf16.empty())
            return {};

        const encoding_string<encoding::utf32> utf32 = encoder<
            encoding::utf16,
            encoding::utf32
        >::encode(utf16);

        const encoding_string<encoding::utf8> utf8 = encoder<
            encoding::utf32,
            encoding::utf8
        >::encode(utf32);

        return utf8.c_str();
    }
};

template <>
class encoder<encoding::utf8, encoding::system> {
public:
    static encoding_string<encoding::system> encode(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return {};

        #if BOOST_OS_WINDOWS
            encoding_string<encoding::utf16> utf16 = encoder<encoding::utf8, encoding::utf16>::encode(utf8);

            const int len = ::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);

            std::string cp932(len, char());

            if (::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, &cp932[0], len, NULL, NULL) > 0)
                return cp932.c_str();
            else
                throw std::runtime_error("conversion error!");
        #else
            return utf8.c_str();
        #endif
    }
};

template <>
class encoder<encoding::utf16, encoding::system> {
public:
    static encoding_string<encoding::system> encode(const encoding_string<encoding::utf16>& utf16)
    {
        #if BOOST_OS_WINDOWS
            const int len = ::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);

            std::string cp932(len, char());

            if (::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, &cp932[0], len, NULL, NULL) > 0)
                return cp932.c_str();
            else
                throw std::runtime_error("conversion error!");
        #else
            return encoder<encoding::utf16, encoding::utf8>::encode(utf16).c_str();
        #endif
    }
};

template <>
class encoder<encoding::utf32, encoding::system> {
public:
    static encoding_string<encoding::system> encode(const encoding_string<encoding::utf32>& utf32)
    {
        #if BOOST_OS_WINDOWS
            encoding_string<encoding::utf16> utf16 = encoder<encoding::utf32, encoding::utf16>::encode(utf32);

            const int len = ::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);

            std::string cp932(len, char());

            if (::WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), -1, &cp932[0], len, NULL, NULL) > 0)
                return cp932.c_str();
            else
                throw std::runtime_error("conversion error!");
        #else
            return encoder<encoding::utf32, encoding::utf8>::encode(utf32).c_str();
        #endif
    }
};

} // namespace shand

#endif // SHAND_ENCODING_STRING_ENCODER_INCLUDE
