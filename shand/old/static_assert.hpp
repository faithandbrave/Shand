#ifndef SHAND_STATIC_ASSERT_INCLUDE
#define SHAND_STATIC_ASSERT_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand {

template <bool> struct static_assertion_faire;
template <> struct static_assertion_faire<true> { enum { value = 1 }; };

#define SHAND_STATIC_ASSERT(Expression) shand::static_assertion_faire<Expression>::value

} // namespace shand

#endif // SHAND_STATIC_ASSERT_INCLUDE

