#ifndef SHAND_ENCODING_STRING_NORMALIZER_INCLUDE
#define SHAND_ENCODING_STRING_NORMALIZER_INCLUDE

// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <stdexcept>
#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#include <Windows.h>
#endif

namespace shand {

#if BOOST_OS_WINDOWS
template <class Encoding>
encoding_string<Encoding> windows_normalize(::NORM_FORM form,
                                      const encoding_string<Encoding>& src)
{
    const encoding_string<encoding::utf16> utf16 = encode<encoding::utf16>(src);
    const int length = ::NormalizeString(
                            form,
                            utf16.c_str(),
                            utf16.raw_str().size(),
                            NULL,
                            0);

    std::wstring composed(length, wchar_t());
    if (::NormalizeString(
            form,
            utf16.c_str(),
            utf16.raw_str().size(),
            &composed[0],
            length) > 0) {
        return encode<Encoding>(encoding_string<encoding::utf16>(composed.c_str()));
    }
    throw std::runtime_error("conversion error");
}
#endif

template <class Encoding>
class normalizer;

template <>
class normalizer<encoding::utf8> {
public:
    static encoding_string<encoding::utf8> compose(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return utf8;

        #if BOOST_OS_WINDOWS
            return windows_normalize(NormalizationC, utf8);
        #else
            static_assert(false, "not implemented");
        #endif
    }

    static encoding_string<encoding::utf8> decompose(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return utf8;

        #if BOOST_OS_WINDOWS
            return windows_normalize(NormalizationD, utf8);
        #else
            static_assert(false, "not implemented");
        #endif
    }

    static encoding_string<encoding::utf8> compatible_compose(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return utf8;

        #if BOOST_OS_WINDOWS
            return windows_normalize(NormalizationKC, utf8);
        #else
            static_assert(false, "not implemented");
        #endif
    }

    static encoding_string<encoding::utf8> compatible_decompose(const encoding_string<encoding::utf8>& utf8)
    {
        if (utf8.empty())
            return utf8;

        #if BOOST_OS_WINDOWS
            return windows_normalize(NormalizationKD, utf8);
        #else
            static_assert(false, "not implemented");
        #endif
    }
};

} // namespace shand

#endif // SHAND_ENCODING_STRING_NORMALIZER_INCLUDE
