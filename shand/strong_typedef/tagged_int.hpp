#ifndef SHAND_TAGGED_INT_INCLUDE
#define SHAND_TAGGED_INT_INCLUDE

// strong typedef for integer types.
//
// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iosfwd>
#include <boost/type_traits/is_integral.hpp>
#include <boost/static_assert.hpp>
#include <boost/operators.hpp>

namespace shand {

template <class Integer, class Tag> // Tag is phantom type
class tagged_int :
        private boost::operators<tagged_int<Integer, Tag> > {

    BOOST_STATIC_ASSERT(boost::is_integral<Integer>::value);

    Integer value_;
public:
    typedef Integer value_type;

    tagged_int(Integer value = 0) : value_(value) {}

    Integer& get() { return value_; }
    const Integer& get() const { return value_; }

    // operators
    bool operator<(const tagged_int& x) const { return value_ < x.value_; }
    bool operator==(const tagged_int& x) const { return value_ == x.value_; }
    tagged_int& operator+=(const tagged_int& x) { value_ += x.value_; return *this; }
    tagged_int& operator-=(const tagged_int& x) { value_ -= x.value_; return *this; }
    tagged_int& operator*=(const tagged_int& x) { value_ *= x.value_; return *this; }
    tagged_int& operator/=(const tagged_int& x) { value_ /= x.value_; return *this; }
    tagged_int& operator%=(const tagged_int& x) { value_ %= x.value_; return *this; }

    tagged_int& operator&=(const tagged_int& x) { value_ &= x.value_; return *this; }
    tagged_int& operator|=(const tagged_int& x) { value_ |= x.value_; return *this; }
    tagged_int& operator^=(const tagged_int& x) { value_ ^= x.value_; return *this; }

    tagged_int& operator++() { ++value_; return *this; }
    tagged_int& operator--() { --value_; return *this; }
};

template <class CharT, class Traits, class Integer, class Tag>
std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const tagged_int<Integer, Tag>& x)
{
    return os << x.get();
}

template <class CharT, class Traits, class Integer, class Tag>
std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, tagged_int<Integer, Tag>& x)
{
    return is >> x.get();
}

} // namespace shand

#endif

