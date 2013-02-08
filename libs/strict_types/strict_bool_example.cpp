// disallow integer/floating point conversion bool
//
// Copyright Akira Takahashi 2013
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <shand/strict_types/bool.hpp>

int main()
{
    shand::strict_bool x = true;
    x = false;
    std::cout << std::boolalpha << x.get() << std::endl;

//  shand::strict_bool y = 3.0; // コンパイルエラー！

//  shand::strict_bool z = true;
//  z = 3.0; // コンパイルエラー！

    // OK
    if (x < true) {}

    // コンパイルエラー！
//  if (x < 3) {}
}
