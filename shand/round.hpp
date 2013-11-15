#ifndef SHAND_ROUND_INCLUDE
#define SHAND_ROUND_INCLUDE

// Round utilities.
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cmath>
#include <type_traits>

namespace shand {

template <class To, class From>
To round_to(From x)
{
    static_assert(std::is_floating_point<From>::value,
                  "from type must be floating point type");

    return static_cast<To>(std::round(x));
}

template <class To, class From>
To ceil_to(From x)
{
    static_assert(std::is_floating_point<From>::value,
                  "from type must be floating point type");

    return static_cast<To>(std::ceil(x));
}

template <class To, class From>
To floor_to(From x)
{
    static_assert(std::is_floating_point<From>::value,
                  "from type must be floating point type");

    return static_cast<To>(std::floor(x));
}

} // namespace shand

#endif // SHAND_ROUND_INCLUDE

