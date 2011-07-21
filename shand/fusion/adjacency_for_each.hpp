#ifndef SHAND_FUSION_ADJACENCY_FOR_EACH_INCLUDE
#define SHAND_FUSION_ADJACENCY_FOR_EACH_INCLUDE

// Boost.Fusion extension. adjacency_for_each algorithm.
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/pop_front.hpp>

namespace shand { namespace fusion {

namespace result_of {

template <class Seq, class F>
struct adjacency_for_each {
    typedef void type;
};

} // namespace result_of

template <class Seq, class F>
inline typename result_of::adjacency_for_each<Seq, F>::type
    adjacency_for_each(const Seq& seq, F f)
{
    namespace fusion = boost::fusion;
    return fusion::for_each(fusion::zip(seq, fusion::pop_front(seq)), f);
}

}} // namespace shand::fusion

#endif // SHAND_FUSION_ADJACENCY_FOR_EACH_INCLUDE
