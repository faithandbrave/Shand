#ifndef SHAND_MPL_EVAL_IF_INCLUDE
#define SHAND_MPL_EVAL_IF_INCLUDE

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand { namespace mpl {

// eval_if_c
template <bool Cond, class Then, class Else>
struct eval_if_c;

template <class Then, class Else>
struct eval_if_c<true, Then, Else> {
    typedef typename Then::type type;
};

template <class Then, class Else>
struct eval_if_c<false, Then, Else> {
    typedef typename Else::type type;
};


// eval_if
template <class Cond, class Then, class Else>
struct eval_if {
    typedef typename eval_if_c<Cond::value, Then, Else>::type type;
};


}} // namespace shand::mpl

#endif // SHAND_MPL_EVAL_IF_INCLUDE

