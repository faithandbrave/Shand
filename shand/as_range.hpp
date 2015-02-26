#ifndef SHAND_AS_RANGE_INCLUDE
#define SHAND_AS_RANGE_INCLUDE

// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <utility>
#include <boost/range/iterator_range_core.hpp>

namespace shand {

template <class Iterator>
boost::iterator_range<Iterator> as_range(std::pair<Iterator, Iterator> p)
{
    return boost::make_iterator_range(p.first, p.second);
}

} // namespace shand

#endif // SHAND_AS_RANGE_INCLUDE

