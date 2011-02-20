#ifndef SHAND_0X_IO_INCLUDE
#define SHAND_0X_IO_INCLUDE

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

