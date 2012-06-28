// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <fstream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <shand/graph_literal.hpp>

enum vertex_type { A, B, C, D, N };
const std::string name = "ABCD";

int main()
{
    typedef
        boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS>
    graph_type;

    using shand::vertex;
    graph_type g = (
                vertex(A) >= vertex(B) &
                vertex(A) >= vertex(C) >= vertex(D)
            );

    std::ofstream file("test.dot");
    boost::write_graphviz(file, g, boost::make_label_writer(name.c_str()));
}

