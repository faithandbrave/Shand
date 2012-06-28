// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/io.hpp>
#include <shand/fusion/adjacency_for_each.hpp>

namespace fusion = boost::fusion;

struct disper {
    template <class Seq>
    void operator()(const Seq& seq) const
    {
        std::cout << seq << std::endl;
    }
};

int main()
{
    const fusion::vector<int, char, double> v(1, 'a', 3.14);

    shand::fusion::adjacency_for_each(v, disper());
}

