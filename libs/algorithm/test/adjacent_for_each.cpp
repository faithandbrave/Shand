// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <utility>
#include <shand/algorithm/adjacent_for_each.hpp>
#include <boost/detail/lightweight_test.hpp>

int main()
{
    {
        const std::vector<int> input = {1, 2, 3};
        const std::vector<std::pair<int, int>> expected = {
            {1, 2},
            {2, 3}
        };
 
        std::vector<std::pair<int, int>> result;
        shand::adjacent_for_each(input, [&result](int a, int b) {
            result.push_back(std::make_pair(a, b));
        });
        BOOST_TEST(result == expected);
    }
    {
        const std::vector<int> input = {1};
        shand::adjacent_for_each(input, [](int, int) {
            BOOST_TEST(false);
        });
    }
    {
        const std::vector<int> input = {};
        shand::adjacent_for_each(input, [](int, int) {
            BOOST_TEST(false);
        });
    }
    return boost::report_errors();
}
