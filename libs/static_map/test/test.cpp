// Compile time fixed capacity map.
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/static_map.hpp>

void construct_and_find_test()
{
    shand::static_map<char, int, 3> map = {
        {'a', 1},
        {'b', 2},
        {'c', 3}
    };

    BOOST_TEST(map.at('a') == 1);
    BOOST_TEST(map.at('b') == 2);
    BOOST_TEST(map.at('c') == 3);
}

void helper_function_test()
{
    shand::pair_maker<char, int> p;
    const auto map = shand::make_static_map(
        p('a', 1),
        p('b', 2),
        p('c', 3)
    );

    BOOST_TEST(map.at('a') == 1);
    BOOST_TEST(map.at('b') == 2);
    BOOST_TEST(map.at('c') == 3);
}

int main()
{
    construct_and_find_test();
    helper_function_test();

    return boost::report_errors();
}
