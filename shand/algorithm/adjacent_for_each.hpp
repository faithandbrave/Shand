#ifndef SHAND_ALGORITHM_ADJACENT_FOR_EACH_INCLUDE
#define SHAND_ALGORITHM_ADJACENT_FOR_EACH_INCLUDE

// Copyright Akira Takahashi 2015
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <iterator>
 
namespace shand {

template <class InputRange, class BinaryFunction>
void adjacent_for_each(const InputRange& range, BinaryFunction f)
{
    // for ADL
    using std::begin;
    using std::end;

    auto first = begin(range);
    auto last = end(range);
 
    if (first == last)
        return;
 
    while (std::next(first) != last) {
        const auto& a = *first;
        ++first;
        const auto& b = *first;
        f(a, b);
    }
}

} // namespace shand

#endif // SHAND_ALGORITHM_ADJACENT_FOR_EACH_INCLUDE

