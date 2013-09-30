// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <deque>
#include <string>
#include <shand/graph/euler_path.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/assign/list_of.hpp>

//        A
//        +
//     -     -
// B +---------+ C
//   | -     - |
//   |    +    |
//   | -     - |
// D +---------+ E

int main()
{
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> Graph;

    enum {A, B, C, D, E, N};

    // House of Santa
    // http://www.mathematische-basteleien.de/house.html
    const std::vector<std::pair<int, int> > edges = {
        {A, B},
        {B, C},
        {C, A},
        {B, D},
        {B, E},
        {C, D},
        {D, E},
        {E, C}
    };

    const Graph g(edges.begin(), edges.end(), N);

    BOOST_TEST(!shand::graph::is_euler_graph(g, A));
    BOOST_TEST(!shand::graph::is_euler_graph(g, B));
    BOOST_TEST(!shand::graph::is_euler_graph(g, C));

    BOOST_TEST(shand::graph::is_euler_graph(g, D));
    BOOST_TEST(shand::graph::is_euler_graph(g, E));

    return boost::report_errors();
}

