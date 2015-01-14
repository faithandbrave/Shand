#ifndef SHAND_TO_WEAK_INCLUDE
#define SHAND_TO_WEAK_INCLUDE

// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <memory>

namespace shand {

// for Initialized lambda captures of C++14
template <class T>
std::weak_ptr<T> to_weak(const std::shared_ptr<T>& sp) BOOST_NOEXCEPT
{
    return sp;
}

} // namespace shand

#endif // SHAND_TO_WEAK_INCLUDE

