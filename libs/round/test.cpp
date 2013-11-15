// Round utilities.
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/round.hpp>

int main()
{
    {
        const int x = shand::round_to<int>(1.4);
        BOOST_TEST(x == 1);

        const int y = shand::round_to<int>(1.5);
        BOOST_TEST(y == 2);
    }
    {
        const int x = shand::round_even_to<int>(1.5);
        BOOST_TEST(x == 2);

        const int y = shand::round_even_to<int>(2.5);
        BOOST_TEST(y == 2);
    }
    {
        const int x = shand::ceil_to<int>(1.4);
        BOOST_TEST(x == 2);
    }
    {
        const int x = shand::floor_to<int>(1.6);
        BOOST_TEST(x == 1);
    }
    return boost::report_errors();
}
