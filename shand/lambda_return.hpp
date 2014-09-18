#ifndef SHAND_LAMBDA_RETURN_INCLUDE
#define SHAND_LAMBDA_RETURN_INCLUDE

// Copyright Akira Takahashi 2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

namespace shand {

class continuation_value {
    bool value_;
public:
    explicit continuation_value(bool value)
        : value_(value) {}

    bool is_continue() const { return value_ == false; }
    bool is_break() const    { return value_ == true; }
};

namespace {
const continuation_value continue_return(false);
const continuation_value break_return(true);
}

} // namespace shand

/*
// example:

template <class Iterator, class F>
void my_for_each(Iterator first, Iterator last, F f)
{
    for (; first != last; ++first) {
        if (f(*first).is_break()) {
            break;
        }
    }
}

#include <iostream>
#include <vector>
int main()
{
    std::vector<int> v = {1, 2, 3};

    my_for_each(v.begin(), v.end(), [](int x) {
        std::cout << x << std::endl;
        return shand::break_return;
    });
}
*/

#endif // SHAND_LAMBDA_RETURN_INCLUDE

