#ifndef SHAND_ENCODING_STRING_ENCODER_INCLUDE
#define SHAND_ENCODING_STRING_ENCODER_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <codecvt>
#include <stdexcept>
#include <boost/predef.h>
#include "./utf16_string.hpp"
#include "./utf8_string.hpp"
#include "./system_string.hpp"

#if BOOST_OS_WINDOWS
#include <Windows.h>
#endif

namespace shand {

template <class From, class To>
class encoder;

template <class Encoding>
class encoder<Encoding, Encoding> {
public:
    static encoding_string<Encoding> encode(const encoding_string<Encoding>& s)
    {
        return s;
    }
};

template <>
class encoder<encoding::utf8, encoding::utf16> {
public:
    static encoding_string<encoding::utf16> encode(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return {};

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
        const std::wstring utf16 = convert.from_bytes(utf8.c_str());

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

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
        const std::string utf8 = convert.to_bytes(utf16.c_str());
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

} // namespace shand

#endif // SHAND_ENCODING_STRING_ENCODER_INCLUDE
