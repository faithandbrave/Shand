#ifndef SHAND_OPTIONAL_ALGORITHM_MAP_FIND_INCLUDE
#define SHAND_OPTIONAL_ALGORITHM_MAP_FIND_INCLUDE

// Shand Optional Algorithm Library
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/optional.hpp>

namespace shand { namespace optional_algorithm {

template <class Map, class Key>
inline boost::optional<typename Map::mapped_type>
    map_find(const Map& m, const Key& key)
{
    typename Map::const_iterator it = m.find(key);
    return it != m.end() ? it->second : boost::optional<typename Map::mapped_type>();
}

} // namespace optional_algorithm

using optional_algorithm::map_find;

} // namespace shand

#endif // SHAND_OPTIONAL_ALGORITHM_MAP_FIND_INCLUDE

