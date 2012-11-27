// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <ctime>
#include <shand/strong_typedef/tagged_int.hpp>
#include <shand/strong_typedef/tagged_int_io.hpp>

struct count_tag {};
struct seconds_tag {};

int main()
{
    shand::tagged_int<std::size_t, count_tag> count = 0;
    shand::tagged_int<std::time_t, seconds_tag> seconds = std::time(0);

    // 異なる型(タグ)間での暗黙変換はできない
//  count = seconds; // コンパイルエラー！型が違う

    std::cout << count << std::endl;
    std::cout << seconds << std::endl;
}

/*
possible output:
0
1353483810
*/

