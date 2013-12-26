#ifndef SHAND_ENCODING_STRING_INCLUDE
#define SHAND_ENCODING_STRING_INCLUDE

// encoding string
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3572.html
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
// - add `encoding_file` class. The class manage endian and BOM.
// - documentation. use GitHub Wiki.

#include <iostream>

namespace shand {

namespace encoding {

struct utf16 {};
struct utf8 {};
struct utf32 {};
struct system {};

} // namespace encoding

template <class Encoding>
class encoding_string;

} // namespace shand

#include "./encoding_string/utf16_string.hpp"
#include "./encoding_string/utf8_string.hpp"
#include "./encoding_string/utf32_string.hpp"
#include "./encoding_string/system_string.hpp"

#include "./encoding_string/encoder.hpp"

namespace shand {

template <class To, class From>
encoding_string<To> encode(const encoding_string<From>& from)
{
    return encoder<From, To>::encode(from);
}

template <class CharT, class Encoding>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const encoding_string<Encoding>& s)
{
    return os << encode<encoding::system>(s).c_str();
}

} // namespace shand

#include "./encoding_string/normalizer.hpp"

namespace shand {

// NFC (Normalization Form Canonical Composition)
// Please don't use this function yet. imcomplete implementation.
template <class Encoding>
encoding_string<Encoding> compose(const encoding_string<Encoding>& s)
{
    return normalizer<Encoding>::compose(s);
}

// NFD (Normalization Form Canonical Decomposition)
// Please don't use this function yet. imcomplete implementation.
template <class Encoding>
encoding_string<Encoding> decompose(const encoding_string<Encoding>& s)
{
    return normalizer<Encoding>::decompose(s);
}

// NFKC (Normalization Form Compatibility Composition)
// Please don't use this function yet. imcomplete implementation.
template <class Encoding>
encoding_string<Encoding> compatible_compose(const encoding_string<Encoding>& s)
{
    return normalizer<Encoding>::compatible_compose(s);
}

// NFKD (Normalization Form Compatibility Decomposition)
// Please don't use this function yet. imcomplete implementation.
template <class Encoding>
encoding_string<Encoding> compatible_decompose(const encoding_string<Encoding>& s)
{
    return normalizer<Encoding>::compatible_decompose(s);
}

} // namespace shand

#endif // SHAND_ENCODING_STRING_INCLUDE

