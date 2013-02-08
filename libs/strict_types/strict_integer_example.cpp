// disallow bool conversion integer
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/strict_types/integer.hpp>

int main()
{
    shand::strict_integer<int> x = 3;
    x = 2;
    std::cout << x.get() << std::endl;

//  shand::strict_integer<int> y = false; // コンパイルエラー！

//  shand::strict_integer<int> z = 3;
//  z = false; // コンパイルエラー！

    // OK
    if (x < 4) {}

    // コンパイルエラー！
//  if (x < false) {}
}
