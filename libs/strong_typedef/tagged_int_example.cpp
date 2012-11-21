// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <ctime>
#include <shand/strong_typedef/tagged_int.hpp>

struct count_tag {};
struct seconds_tag {};

int main()
{
	shand::tagged_int<std::size_t, count_tag> count = 0;
	shand::tagged_int<std::time_t, seconds_tag> seconds = std::time(0);

    // �قȂ�^(�^�O)�Ԃł̈Öٕϊ��͂ł��Ȃ�
//	count = seconds; // �R���p�C���G���[�I�^���Ⴄ

	std::cout << count << std::endl;
	std::cout << seconds << std::endl;
}

/*
possible output:
0
1353483810
*/

