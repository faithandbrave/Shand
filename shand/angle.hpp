#ifndef SHAND_ANGLE_INCLUDE
#define SHAND_ANGLE_INCLUDE

// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cmath>
#include <boost/math/constants/constants.hpp>
#include "./strong_typedef/tagged_float.hpp"

namespace shand {

struct degree_tag {};
struct radian_tag {};

template <class FloatingPoint>
using degree_t = shand::tagged_float<FloatingPoint, degree_tag>;
using degree_f = degree_t<float>;
using degree_d = degree_t<double>;
using degree_ld = degree_t<long double>;

template <class FloatingPoint>
using radian_t = shand::tagged_float<FloatingPoint, radian_tag>;
using radian_f = radian_t<float>;
using radian_d = radian_t<double>;
using radian_ld = radian_t<long double>;

namespace detail {
    template <class FloatingPoint>
    void angle_cast_impl(const degree_t<FloatingPoint>& x, radian_t<FloatingPoint>& result)
    {
        result.get() =
            x.get() * boost::math::constants::pi<FloatingPoint>() / static_cast<FloatingPoint>(180.0);
    }

    template <class FloatingPoint>
    void angle_cast_impl(const radian_t<FloatingPoint>& x, degree_t<FloatingPoint>& result)
    {
        result.get() =
            x.get() * static_cast<FloatingPoint>(180.0) / boost::math::constants::pi<FloatingPoint>();
    }
} // namespace detail

template <class ToAngle, class FromAngle>
ToAngle angle_cast(const FromAngle& x)
{
    ToAngle result;
    detail::angle_cast_impl(x, result);
    return result;
}

// math functions
template <class FloatingPoint>
radian_t<FloatingPoint> sin(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::sin(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> cos(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::cos(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> tan(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::tan(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> asin(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::asin(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> acos(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::acos(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> atan(const radian_t<FloatingPoint>& x)
{
    return radian_t<FloatingPoint>(std::atan(x.get()));
}

template <class FloatingPoint>
radian_t<FloatingPoint> atan2(const FloatingPoint& y,
                              const FloatingPoint& x)
{
    return radian_t<FloatingPoint>(std::atan2(y, x));
}

} // namespace shand

#endif // SHAND_ANGLE_INCLUDE

