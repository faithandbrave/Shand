// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/angle.hpp>

int main()
{
    shand::degree_f deg(45.0f);
    shand::radian_f rad = shand::angle_cast<shand::radian_f>(deg);

    std::cout << rad.get() << std::endl;

//  shand::sin(deg); // compilation error
    shand::radian_f sin_result = shand::sin(rad);
    std::cout << sin_result.get() << std::endl;
}
