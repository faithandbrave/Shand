#ifndef SHAND_MPL_IDENTITY_INCLUDE
#define SHAND_MPL_IDENTITY_INCLUDE

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace shand { namespace mpl {

template <class Type>
struct identity {
    typedef Type type;
};

}} // namespace shand::mpl

#endif // SHAND_MPL_IDENTITY_INCLUDE

