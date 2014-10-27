#ifndef SHAND_STATIC_MAP_INCLUDE
#define SHAND_STATIC_MAP_INCLUDE

// Compile time fixed capacity map.
//
// Copyright Akira Takahashi, myoukaku 2013-2014.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <initializer_list>
#include <type_traits>
#include <boost/container/static_vector.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/lower_bound.hpp>

namespace shand {

template <class Key, class T, std::size_t N, class Compare=std::less<Key>>
class static_map {
    using value_type = std::pair<Key, T>;
    boost::container::static_vector<value_type, N> cont_;
public:
    static_map(std::initializer_list<value_type> init)
        : cont_(init.begin(), init.end())
    {
        boost::sort(cont_, [](const value_type& a, const value_type& b) {
            return Compare()(a.first, b.first); 
        });
    }

    template <class KeyType>
    const T& at(const KeyType& key) const
    {
        auto it = boost::lower_bound(cont_, key,
                    [](const value_type& a, const KeyType& b) {
                        return Compare()(a.first, b);
                    });

        if (it != cont_.end()) {
            if (!Compare()(it->first, key) && !Compare()(key, it->first)) {
                return it->second;
            }
        }
        throw std::out_of_range("out of range error");
    }
};

// usage :
//
// enum class Color {
//    Blue,
//    Yellow,
//    Red
// };
//
// shand::pair_maker<Color, const char*> p;
// const auto map = shand::make_static_map(
//     p(Color::Blue, "AAA"),
//     p(Color::Yellow, "BBB"),
//     p(Color::Red, "CCC")
// );
// 
// std::string s = map.at(Color::Blue);
template <class Key, class T>
struct pair_maker {
    std::pair<Key, T> operator()(Key&& key, T&& value) const
    {
        return {std::move(key), std::move(value)};
    }
};

template <class... Keys, class... Ts>
auto make_static_map(std::pair<Keys, Ts>&&... args)
    -> static_map<
            typename std::common_type<Keys...>::type,
            typename std::common_type<Ts...>::type,
            sizeof...(Keys)>
{
    return static_map<
                typename std::common_type<Keys...>::type,
                typename std::common_type<Ts...>::type,
                sizeof...(Keys)>({args...});
}

} // namespace shand

#endif // SHAND_STATIC_MAP_INCLUDE

