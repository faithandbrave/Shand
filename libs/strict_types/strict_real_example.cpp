// disallow bool conversion floating point
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/strict_types/real.hpp>

int main()
{
    shand::strict_real<float> x = 3.0f;
    x = 2.0f;
    std::cout << x.get() << std::endl;

//  shand::strict_real<float> y = false; // コンパイルエラー！

//  shand::strict_real<float> z = 3.0f;
//  z = false; // コンパイルエラー！

    // OK
    if (x < 4.0f) {}

    // コンパイルエラー！
//  if (x < false) {}
}
