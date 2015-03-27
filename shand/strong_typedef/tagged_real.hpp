#ifndef SHAND_TAGGED_REAL_INCLUDE
#define SHAND_TAGGED_REAL_INCLUDE

// strong typedef for floating point types.
//
// Copyright Akira Takahashi 2012-2015.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/static_assert.hpp>
#include <boost/operators.hpp>
#include <boost/geometry/util/math.hpp>

#if !defined(BOOST_NO_CXX11_NOEXCEPT)
    #define SHAND_NOEXCEPT_COND(cond) noexcept(cond)
    #define SHAND_NOEXCEPT_IF(expr) noexcept(noexcept(expr))
#else
    #define SHAND_NOEXCEPT_COND(cond)
    #define SHAND_NOEXCEPT_IF(expr)
#endif

namespace shand {

template <class FloatingPoint, class Tag> // Tag is phantom type
class tagged_real :
        private boost::operators<tagged_real<FloatingPoint, Tag> > {

    BOOST_STATIC_ASSERT(boost::is_floating_point<FloatingPoint>::value);

    FloatingPoint value_;
public:
    typedef FloatingPoint value_type;

    explicit tagged_real(FloatingPoint value = 0)
        SHAND_NOEXCEPT_COND(boost::has_nothrow_copy_constructor<FloatingPoint>::value)
        : value_(value) {}

    FloatingPoint& get() BOOST_NOEXCEPT { return value_; }
    const FloatingPoint& get() const BOOST_NOEXCEPT { return value_; }

    // operators
    bool operator<(const tagged_real& x) const SHAND_NOEXCEPT_IF(value_ < x.value_)
        { return value_ < x.value_; }
    tagged_real& operator+=(const tagged_real& x) SHAND_NOEXCEPT_IF(value_ += x.value_)
        { value_ += x.value_; return *this; }
    tagged_real& operator-=(const tagged_real& x) SHAND_NOEXCEPT_IF(value_ -= x.value_)
        { value_ -= x.value_; return *this; }
    tagged_real& operator*=(const tagged_real& x) SHAND_NOEXCEPT_IF(value_ *= x.value_)
        { value_ *= x.value_; return *this; }
    tagged_real& operator/=(const tagged_real& x) SHAND_NOEXCEPT_IF(value_ /= x.value_)
        { value_ /= x.value_; return *this; }

    bool equals(const tagged_real& x) const SHAND_NOEXCEPT_IF(boost::geometry::math::equals(value_, x.value_))
    {
        return boost::geometry::math::equals(value_, x.value_);
    }
};

} // namespace shand

#endif

