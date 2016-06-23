#define BOOST_STACKTRACE_HEADER_ONLY
#define BOOST_STACKTRACE_USE_BACKTRACE
#include <iostream>
#include <shand/trace_value.hpp>

shand::trace_value<int> value;

void f()
{
    value = 1;
}

int main()
{
    f();
    value.output_trace(std::cout);
}

/*
output:
 0# boost::stacktrace::detail::backtrace_holder::backtrace_holder()
 1# boost::stacktrace::detail::backtrace_holder::backtrace_holder()
 2# boost::stacktrace::stacktrace::stacktrace()
 3# boost::stacktrace::stacktrace::stacktrace()
 4# shand::trace_value<int>& shand::trace_value<int>::modify_this<shand::trace_value<int>::operator=(int)::'lambda'()>(shand::trace_value<int>::operator=(int)::'lambda'())
 5# shand::trace_value<int>::operator=(int)
 6# f()
 7# main
 8# start
*/
