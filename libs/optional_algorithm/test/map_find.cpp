// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <map>
#include <string>
#include <boost/detail/lightweight_test.hpp>

#include <shand/optional_algorithm/map_find.hpp>

int main()
{
    std::map<std::string, int> m;

    m["Akira"]  = 24;
    m["Millia"] = 16;
    m["Johnny"] = 38;

    if (boost::optional<int> value = shand::map_find(m, "Akira"))
        BOOST_TEST(value.get() == 24);
    else
        BOOST_ERROR("Not Found");

	return boost::report_errors();
}

