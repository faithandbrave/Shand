#ifndef SHAND_OPTIONAL_ALGORITHM_FIND_IF_INCLUDE
#define SHAND_OPTIONAL_ALGORITHM_FIND_IF_INCLUDE

// Shand Optional Algorithm Library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/optional.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/algorithm/find_if.hpp>

namespace shand { namespace optional_algorithm {

template <class SinglePassRange, class UnaryPredicate>
inline boost::optional<typename boost::range_reference<SinglePassRange>::type>
    find_if(SinglePassRange& r, UnaryPredicate pred)
{
    typename boost::range_iterator<SinglePassRange>::type it = boost::find_if(r, pred);
    if (it != boost::end(r)) {
        return *it;
    }
    return boost::none;
}

template <class SinglePassRange, class UnaryPredicate>
inline boost::optional<typename boost::range_reference<const SinglePassRange>::type>
    find_if(const SinglePassRange& r, UnaryPredicate pred)
{
    typename boost::range_iterator<const SinglePassRange>::type it = boost::find_if(r, pred);
    if (it != boost::end(r)) {
        return *it;
    }
    return boost::none;
}

} // namespace optional_algorithm

using optional_algorithm::find_if;

} // namespace shand


#endif // SHAND_OPTIONAL_ALGORITHM_FIND_IF_INCLUDE

