#ifndef SHAND_0X_IO_INCLUDE
#define SHAND_0X_IO_INCLUDE

// Copyright Akira Takahashi 2007
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <tuple>
#include <string>

template <class Head, class... Tail>
void print_detail(std::size_t count, const std::string& fmt, const Head& head, const Tail&... tail)
{
	std::cout << head << std::endl;

	if (count > 0)
		print_detail(count-1, fmt, tail...);
}

template <class... Args>
void print(const std::string& fmt, const Args&... args)
{
	print_detail(sizeof...(args), fmt, args...);
}

#endif // SHAND_0X_IO_INCLUDE

