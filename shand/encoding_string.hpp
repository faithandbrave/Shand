#ifndef SHAND_ENCODING_STRING_INCLUDE
#define SHAND_ENCODING_STRING_INCLUDE

// encoding string
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3572.html
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand {

namespace encoding {

struct utf8 {};
struct utf16 {}; // not implemented
struct utf32 {}; // not implemented
struct system {}; // not implemented

} // namespace encoding

template <class Encoding>
class encoding_string;

} // namespace shand

#include "./encoding_string/utf8_string.hpp"

#endif // SHAND_ENCODING_STRING_INCLUDE

