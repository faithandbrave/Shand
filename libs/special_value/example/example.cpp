// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/special_value.hpp>

enum class PopType { Root };
std::string popToString(PopType) { return "Root"; }

int main()
{
    shand::special_value<std::size_t, PopType> pop_count = 1u;
//  pop_count = PopType::Root;

    pop_count.on_value([](std::size_t value) {
        std::cout << value << std::endl;
    })
    .on_enum([](PopType pop) {
        std::cout << popToString(pop) << std::endl;
    });
}
