#ifndef SHAND_STRICT_TYPES_INTEGER_INCLUDE
#define SHAND_STRICT_TYPES_INTEGER_INCLUDE

// disallow bool conversion integer
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <boost/operators.hpp>

namespace shand {

template <class T>
class strict_integer :
        private boost::operators<strict_integer<T>> {
    static_assert(std::is_integral<T>{}, "T should integral type");
    static_assert(!std::is_same<T, bool>{}, "T shouldn't bool type");

    T value_;
public:
    typedef T value_type;

    strict_integer(bool) = delete;
    strict_integer(T value = 0) : value_(value) {}

    T& get() { return value_; }
    const T& get() const { return value_; }

    strict_integer& operator=(bool) = delete;
    strict_integer& operator=(T x)
    {
        value_ = x;
        return *this;
    }

    // operators
    bool operator<(const strict_integer& x) const { return value_ < x.value_; }
    bool operator==(const strict_integer& x) const { return value_ == x.value_; }
    strict_integer& operator+=(const strict_integer& x) { value_ += x.value_; return *this; }
    strict_integer& operator-=(const strict_integer& x) { value_ -= x.value_; return *this; }
    strict_integer& operator*=(const strict_integer& x) { value_ *= x.value_; return *this; }
    strict_integer& operator/=(const strict_integer& x) { value_ /= x.value_; return *this; }
    strict_integer& operator%=(const strict_integer& x) { value_ %= x.value_; return *this; }

    strict_integer& operator&=(const strict_integer& x) { value_ &= x.value_; return *this; }
    strict_integer& operator|=(const strict_integer& x) { value_ |= x.value_; return *this; }
    strict_integer& operator^=(const strict_integer& x) { value_ ^= x.value_; return *this; }

    strict_integer& operator++() { ++value_; return *this; }
    strict_integer& operator--() { --value_; return *this; }
};

} // namespace shand

#endif // SHAND_STRICT_TYPES_INTEGER_INCLUDE

