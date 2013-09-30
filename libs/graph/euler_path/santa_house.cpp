// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <deque>
#include <string>
#include <shand/graph/euler_path.hpp>
#include <boost/graph/adjacency_list.hpp>

enum {A, B, C, D, E, N};
const std::string name = "ABCDE";

int main()
{
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

    // House of Santa (Japanese name is "サンタクロースの家") : http://ameblo.jp/masanori432/entry-10058793629.html
    // path variation :  http://www.mathematische-basteleien.de/house.html
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
    std::deque<vertex_desc> path;

    if (!shand::graph::euler_path(g, E, [&path] (vertex_desc v) { path.push_front(v); })) {
        std::cout << "euler path failed" << std::endl;
        return 1;
    }

    BOOST_FOREACH (const vertex_desc& v, path) {
        std::cout << name[v] << std::endl;
    }
}

/*
output:
E
B
A
C
B
D
C
E
D

*/

