#ifndef SHAND_TAGGED_REAL_IO_INCLUDE
#define SHAND_TAGGED_REAL_IO_INCLUDE

// strong typedef for floating point types.
//
// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include "./tagged_real.hpp"

namespace shand {

template <class CharT, class Traits, class FloatingPoint, class Tag>
std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const tagged_real<FloatingPoint, Tag>& x)
{
    return os << x.get();
}

template <class CharT, class Traits, class FloatingPoint, class Tag>
std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, tagged_real<FloatingPoint, Tag>& x)
{
    return is >> x.get();
}

} // namespace shand

#endif

