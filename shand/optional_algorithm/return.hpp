#ifndef SHAND_OPTIONAL_ALGORITHM_RETURN_INCLUDE
#define SHAND_OPTIONAL_ALGORITHM_RETURN_INCLUDE

// Shand Optional Algorithm Library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/optional.hpp>

namespace shand {

template <class T>
inline boost::optional<T&> optional_return(bool cond, T& then)
{
    return cond ? boost::optional<T&>(then) : boost::optional<T&>();
}

template <class T>
inline boost::optional<const T&> optional_return(bool cond, const T& then)
{
    return cond ? boost::optional<const T&>(then) : boost::optional<const T&>();
}

} // namespace shand

#endif // SHAND_OPTIONAL_ALGORITHM_RETURN_INCLUDE

