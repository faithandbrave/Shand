#ifndef SHAND_ENABLE_IF_INCLUDE
#define SHAND_ENABLE_IF_INCLUDE

// Copyright 2003 (c) The Trustees of Indiana University.
////    Authors: Jaakko Jarvi (jajarvi at osl.iu.edu)
//             Jeremiah Willcock (jewillco at osl.iu.edu)
//             Andrew Lumsdaine (lums at osl.iu.edu)
// 
// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand {

// enable_if
template <bool, class Type = void>
struct enable_if_c {
    typedef Type type;
};

template <class Type>
struct enable_if_c<false, Type> {};

template <class Cond, class Type = void> 
struct enable_if : public enable_if_c<Cond::value, Type> {};


// disable_if
template <bool, class Type = void>
struct disable_if_c {
    typedef Type type;
};

template <class Type>
struct disable_if_c<true, Type> {};

template <class Cond, class Type = void> 
struct disable_if : public disable_if_c<Cond::value, Type> {};

} // namespace shand

#endif // SHAND_ENABLE_IF_INCLUDE
