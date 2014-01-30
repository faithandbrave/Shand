// Copyright Akira Takahashi 2012-2014
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <shand/strong_typedef/tagged_int.hpp>

#include <unordered_map>
#include <boost/unordered_map.hpp>

struct tag {};
typedef shand::tagged_int<int, tag> integer;

int main ()
{
    {
        std::unordered_map<integer, char> m;
        m.insert(std::make_pair(integer(3), 'a'));
    }
    {
        boost::unordered_map<integer, char> m;
        m.insert(std::make_pair(integer(3), 'a'));
    }

    return boost::report_errors();
}

