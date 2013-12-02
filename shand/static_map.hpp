#ifndef SHAND_STATIC_MAP_INCLUDE
#define SHAND_STATIC_MAP_INCLUDE

// Compile time fixed capacity map.
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <initializer_list>
#include <boost/container/static_vector.hpp>
#include <boost/range/algorithm/find_if.hpp>

namespace shand {

template <class Key, class T, std::size_t N, class Compare=std::less<T>>
class static_map {
    using value_type = std::pair<Key, T>;
    boost::container::static_vector<value_type, N> cont_;
public:
    static_map(std::initializer_list<value_type> init)
        : cont_(init.begin(), init.end()) {}

    template <class KeyType>
    const T& at(const KeyType& key) const
    {
        auto it = boost::find_if(cont_, [key](const value_type& x) {
            return !Compare()(x.first, key) && !Compare()(key, x.first);
        });
        if (it == cont_.end()) {
            throw std::out_of_range("out of range error");
        }
        return it->second;
    }
};

} // namespace shand

#endif // SHAND_STATIC_MAP_INCLUDE

