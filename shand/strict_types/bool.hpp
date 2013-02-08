#ifndef SHAND_STRICT_TYPES_BOOL_INCLUDE
#define SHAND_STRICT_TYPES_BOOL_INCLUDE

// disallow integer/floating point conversion bool
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <boost/operators.hpp>

namespace shand {

class strict_bool :
        private boost::operators<strict_bool> {
    bool value_;
public:
    typedef bool value_type;

    strict_bool(bool value = false)
		: value_(value) {}

	template <class T>
    strict_bool(T) = delete;

    bool& get() { return value_; }
    const bool& get() const { return value_; }

    strict_bool& operator=(bool x)
    {
        value_ = x;
        return *this;
    }

	template <class T>
    strict_bool& operator=(T) = delete;

    // operators
    bool operator<(const strict_bool& x) const { return value_ < x.value_; }
    bool operator==(const strict_bool& x) const { return value_ == x.value_; }

	explicit operator bool() const
	{
		return value_;
	}
};

} // namespace shand

#endif // SHAND_STRICT_TYPES_BOOL_INCLUDE

