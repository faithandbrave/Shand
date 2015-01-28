// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/optional.hpp>
#include <shand/match.hpp>

int main()
{
    boost::optional<int> a = 3;
    shand::match(a, [](int& x) {
        std::cout << x << std::endl;
    });
 
    boost::optional<int> b;
    shand::match(b, [] {
        std::cout << "none" << std::endl;
    });
 
    // 2 arguments version
    shand::match(a,
        [](int& x) { std::cout << x << std::endl; },
        [] { std::cout << "none" << std::endl; }
    );
}

/*
output:
3
none
3
*/

