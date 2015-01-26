// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>
#include <shand/algorithm/adjacent_for_each.hpp>
 
int main()
{
    const std::vector<int> v = {1, 2, 3};
 
    shand::adjacent_for_each(v, [](int a, int b) {
        std::cout << a << " : " << b << std::endl;
    });
}

/*
output:
1 : 2
2 : 3
*/
