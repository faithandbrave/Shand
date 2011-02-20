#ifndef SHAND_OPTIONAL_ALGORITHM_MIN_ELEMENT_INCLUDE
#define SHAND_OPTIONAL_ALGORITHM_MIN_ELEMENT_INCLUDE

// Shand Optional Algorithm Library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "./return.hpp"
#include <boost/range/reference.hpp>
#include <boost/range/algorithm/min_element.hpp>

namespace shand { namespace optional_algorithm {

template <class ForwardRange>
inline boost::optional<typename boost::range_reference<ForwardRange>::type>
	min_element(ForwardRange& r)
{
	typename boost::range_iterator<ForwardRange>::type it = boost::min_element(r);
	return optional_return(it != boost::end(r), *it);
}

template <class ForwardRange>
inline boost::optional<typename boost::range_reference<const ForwardRange>::type>
	min_element(const ForwardRange& r)
{
	typename boost::range_iterator<const ForwardRange>::type it = boost::min_element(r);
	return optional_return(it != boost::end(r), *it);
}

template <class ForwardRange, class BinaryPredicate>
inline boost::optional<typename boost::range_reference<ForwardRange>::type>
	min_element(ForwardRange& r, BinaryPredicate pred)
{
	typename boost::range_iterator<ForwardRange>::type it = boost::min_element(r, pred);
	return optional_return(it != boost::end(r), *it);
}

template <class ForwardRange, class BinaryPredicate>
inline boost::optional<typename boost::range_reference<const ForwardRange>::type>
	min_element(const ForwardRange& r, BinaryPredicate pred)
{
	typename boost::range_iterator<const ForwardRange>::type it = boost::min_element(r, pred);
	return optional_return(it != boost::end(r), *it);
}

} // namespace optional_algorithm

using optional_algorithm::min_element;

} // namespace shand

#endif // SHAND_OPTIONAL_ALGORITHM_MIN_ELEMENT_INCLUDE

