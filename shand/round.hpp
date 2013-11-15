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

// round to the nearest integer value
template <class To, class From>
To round_to(From x)
{
    static_assert(std::is_floating_point<From>::value,
                  "from type must be floating point type");

    return static_cast<To>(std::round(x));
}

// round to the nearest even
// a.k.a banker's rounding
template <class To, class From>
To round_even_to(From x)
{
    static_assert(std::is_floating_point<From>::value,
                  "from type must be floating point type");

    To t0 = static_cast<To>(x);
    To t1 = t0;

    ++t1;

    auto diff0 = x - t0;
    auto diff1 = t1 - x;
    if (diff0 == diff1)
    {
        if (t0 & 1)
            return t1;
        return t0;
    }
    else if (diff0 < diff1)
        return t0;
    return t1;
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

