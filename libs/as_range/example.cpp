// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <map>
#include <string>
#include <shand/as_range.hpp>

int main()
{
    const std::multimap<int, std::string> m = {
        {1, "apple"},
        {2, "gorrila"},
        {1, "bugle"}
    };

    for (const auto& x : shand::as_range(m.equal_range(1))) {
        std::cout << x.second << std::endl;
    }
}

/*
output:
apple
bugle
*/
