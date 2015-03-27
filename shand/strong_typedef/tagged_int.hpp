#ifndef SHAND_TAGGED_INT_INCLUDE
#define SHAND_TAGGED_INT_INCLUDE

// strong typedef for integer types.
//
// Copyright Akira Takahashi 2012-2015.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/static_assert.hpp>
#include <boost/operators.hpp>
#include <boost/functional/hash.hpp>
#include <functional>

#if defined(BOOST_NO_CXX11_NOEXCEPT)
    #define SHAND_NOEXCEPT_COND(cond) noexcept(cond)
    #define SHAND_NOEXCEPT_IF(expr) noexcept(noexcept(expr))
#else
    #define SHAND_NOEXCEPT_COND(cond)
    #define SHAND_NOEXCEPT_IF(expr)
#endif

namespace shand {

template <class Integer, class Tag> // Tag is phantom type
class tagged_int :
        private boost::operators<tagged_int<Integer, Tag> > {

    BOOST_STATIC_ASSERT(boost::is_integral<Integer>::value);

    Integer value_;
public:
    typedef Integer value_type;

    explicit tagged_int(Integer value = 0)
        SHAND_NOEXCEPT_COND(boost::has_nothrow_copy_constructor<Integer>::value)
        : value_(value) {}

    Integer& get() BOOST_NOEXCEPT { return value_; }
    const Integer& get() const BOOST_NOEXCEPT { return value_; }

    // operators
    bool operator<(const tagged_int& x) const SHAND_NOEXCEPT_IF(value_ < x.value_)
        { return value_ < x.value_; }
    bool operator==(const tagged_int& x) const SHAND_NOEXCEPT_IF(value_ == x.value_)
        { return value_ == x.value_; }

    tagged_int& operator+=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ += x.value_)
        { value_ += x.value_; return *this; }
    tagged_int& operator-=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ -= x.value_)
        { value_ -= x.value_; return *this; }
    tagged_int& operator*=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ *= x.value_)
        { value_ *= x.value_; return *this; }
    tagged_int& operator/=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ /= x.value_)
        { value_ /= x.value_; return *this; }
    tagged_int& operator%=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ %= x.value_)
        { value_ %= x.value_; return *this; }

    tagged_int& operator&=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ &= x.value_)
        { value_ &= x.value_; return *this; }
    tagged_int& operator|=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ |= x.value_)
        { value_ |= x.value_; return *this; }
    tagged_int& operator^=(const tagged_int& x) SHAND_NOEXCEPT_IF(value_ ^= x.value_)
        { value_ ^= x.value_; return *this; }

    tagged_int& operator++() SHAND_NOEXCEPT_IF(++value_)
        { ++value_; return *this; }
    tagged_int& operator--() SHAND_NOEXCEPT_IF(--value_)
        { --value_; return *this; }
};

// Boost hash support
template <class Integer, class Tag>
std::size_t hash_value(const tagged_int<Integer, Tag>& x) SHAND_NOEXCEPT_IF(boost::hash_value(x.get()))
{
    return boost::hash_value(x.get());
}

} // namespace shand


// Standard hash support
#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

namespace std {

template <class Integer, class Tag>
struct hash<shand::tagged_int<Integer, Tag> > {
    size_t operator()(const shand::tagged_int<Integer, Tag>& x) const BOOST_NOEXCEPT
    {
        return ::std::hash<Integer>()(x.get());
    }
};


} // namespace std

#endif

#undef SHAND_NOEXEPT_IF

#endif

