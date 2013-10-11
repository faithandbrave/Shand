// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
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
    const std::vector<std::pair<int, int> > edges = boost::assign::list_of
        (std::make_pair(A, B))
        (std::make_pair(B, C))
        (std::make_pair(C, A))
        (std::make_pair(B, D))
        (std::make_pair(B, E))
        (std::make_pair(C, D))
        (std::make_pair(D, E))
        (std::make_pair(E, C))
    ;

    const Graph g(edges.begin(), edges.end(), N);

    BOOST_TEST(!shand::graph::has_euler_path(g, vertex(A, g)));
    BOOST_TEST(!shand::graph::has_euler_path(g, vertex(B, g)));
    BOOST_TEST(!shand::graph::has_euler_path(g, vertex(C, g)));

    BOOST_TEST(shand::graph::has_euler_path(g, vertex(D, g)));
    BOOST_TEST(shand::graph::has_euler_path(g, vertex(E, g)));

    return boost::report_errors();
}

