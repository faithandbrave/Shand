#ifndef SHAND_TYPE_TRAITS_IS_CALLABLE_INCLUDE
#define SHAND_TYPE_TRAITS_IS_CALLABLE_INCLUDE

// Copyright Mikael Persson 2011
// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// 
// Reference implementation is follow:
// http://stackoverflow.com/questions/5100015/c-metafunction-to-determine-whether-a-type-is-callable/5100602#5100602
#include <utility>
#include <type_traits>
 
namespace shand {

namespace impl {

template <class PotentiallyCallable, class... Args>
struct is_callable {
    typedef char (&no)  [1];
    typedef char (&yes) [2];
 
    template <class T> struct dummy;
 
    template <class CheckType>
    static yes check(dummy<decltype(std::declval<CheckType>()(std::declval<Args>()...))> *);
    template <class CheckType>
    static no check(...);
 
    static const bool value = sizeof(check<PotentiallyCallable>(0)) == sizeof(yes);
};

} // namespace impl
 
template <class PotentiallyCallable, class... Args>
struct is_callable
    : std::integral_constant<
            bool,
            shand::impl::is_callable<PotentiallyCallable, Args...>::value
    > {};
 
} // namespace shand

#endif // SHAND_TYPE_TRAITS_IS_CALLABLE_INCLUDE

