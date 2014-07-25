// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/immutable_vector.hpp>

int main()
{
    // add element, modify element, etc...
    shand::vector_builder<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // end modify
    shand::immutable_vector<int> iv(std::move(v));

    for (int x : iv) {
        std::cout << x << std::endl;
    }
}

