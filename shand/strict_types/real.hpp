#ifndef SHAND_STRICT_TYPES_REAL_INCLUDE
#define SHAND_STRICT_TYPES_REAL_INCLUDE

// disallow bool conversion floating point
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <boost/operators.hpp>
#include <boost/geometry/util/math.hpp>

namespace shand {

template <class T>
class strict_real :
        private boost::operators<strict_real<T>> {
    static_assert(std::is_floating_point<T>{}, "T should floating point type");
    static_assert(!std::is_same<T, bool>{}, "T shouldn't bool type");

    T value_;
public:
    typedef T value_type;

    strict_real(bool) = delete;
    strict_real(T value = 0) : value_(value) {}

    T& get() { return value_; }
    const T& get() const { return value_; }

    strict_real& operator=(bool) = delete;
    strict_real& operator=(T x)
    {
        value_ = x;
        return *this;
    }

    // operators
    bool operator<(const strict_real& x) const { return value_ < x.value_; }
    strict_real& operator+=(const strict_real& x) { value_ += x.value_; return *this; }
    strict_real& operator-=(const strict_real& x) { value_ -= x.value_; return *this; }
    strict_real& operator*=(const strict_real& x) { value_ *= x.value_; return *this; }
    strict_real& operator/=(const strict_real& x) { value_ /= x.value_; return *this; }
    strict_real& operator%=(const strict_real& x) { value_ %= x.value_; return *this; }

    bool equals(const strict_real& x) const
    {
        return boost::geometry::math::equals(value_, x.value_);
    }
};

} // namespace shand

#endif // SHAND_STRICT_TYPES_REAL_INCLUDE

