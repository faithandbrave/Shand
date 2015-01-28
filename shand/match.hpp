#ifndef SHAND_MATCH_INCLUDE
#define SHAND_MATCH_INCLUDE

// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Inspired by follow :
// https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/31glnrmsNaY
// https://github.com/viboes/tags/blob/master/doc/proposals/match/DXXXX_Match.md

#include <shand/type_traits/is_callable.hpp>
#include <boost/optional.hpp>

namespace shand {
 
namespace match_detail {
 
template <class Optional, class F>
void call_value(Optional& opt, F f, std::true_type)
{
    f(opt.get());
}
 
template <class Optional, class F>
void call_value(Optional&, F, std::false_type) {}
 
template <class F>
void call_none(F f, std::true_type)
{
    f();
}
 
template <class F>
void call_none(F, std::false_type) {}
 
} // namespace match_detail
 

// for `boost::optional`
//
// `F` is `R(T&)` or `R(const T&)` or `R()`.
// 
// `F` is `R(T&)` or `R(const T&)` :
//   If `x` has value, call `f(x.get())`, Otherwise not call.
// `F` is `R()` :
//   If `x` is `none`, call `f()`, Otherwise not call.
template <class T, class F>
void match(boost::optional<T>& x, F f)
{
    if (x) {
        match_detail::call_value(x, f, shand::is_callable<F, T&>());
    }
    else {
        match_detail::call_none(f, shand::is_callable<F>());
    }
}
 
template <class T, class F>
void match(const boost::optional<T>& x, F f)
{
    if (x) {
        match_detail::call_value(x, f, shand::is_callable<F, const T&>());
    }
    else {
        match_detail::call_none(f, shand::is_callable<F>());
    }
}
 

template <class T, class F1, class F2>
void match(boost::optional<T>& x, F1 f1, F2 f2)
{
    if (x) {
        match_detail::call_value(x, f1, shand::is_callable<F1, T&>());
        match_detail::call_value(x, f2, shand::is_callable<F2, T&>());
    }
    else {
        match_detail::call_none(f1, shand::is_callable<F1>());
        match_detail::call_none(f2, shand::is_callable<F2>());
    }
}
 
template <class T, class F1, class F2>
void match(const boost::optional<T>& x, F1 f1, F2 f2)
{
    if (x) {
        match_detail::call_value(x, f1, shand::is_callable<F1, const T&>());
        match_detail::call_value(x, f2, shand::is_callable<F2, const T&>());
    }
    else {
        match_detail::call_none(f1, shand::is_callable<F1>());
        match_detail::call_none(f2, shand::is_callable<F2>());
    }
}
 
} // namespace shand

#endif // SHAND_MATCH_INCLUDE

