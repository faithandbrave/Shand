// Copyright Akira Takahashi 2014.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Original implementation's license :
// Copyright Jens Maurer 2000
// Copyright Steven Watanabe 2010-2011
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <random>
#include <shand/random/random_device.hpp>

int main()
{
    shand::random_device_32 rd32;
    std::cout << rd32() << std::endl;
    std::cout << rd32() << std::endl;

    shand::random_device_64 rd64;
    std::cout << rd64() << std::endl;
    std::cout << rd64() << std::endl;

    // make 32 bit seed
    std::mt19937 gen(rd32());

    // make 64 bit seed
    std::mt19937_64 gen64(rd64());
}
