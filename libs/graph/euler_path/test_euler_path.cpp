// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/lightweight_test.hpp>
#include <deque>
#include <shand/graph/euler_path.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/assign/list_of.hpp>

template <class Container, class Graph>
class add_path {
    Container& path_;
    const Graph& g_;
public:
    add_path(Container& path, const Graph& g) : path_(path), g_(g) {}

    template <class VertexDescriptor>
    void operator()(VertexDescriptor v)
    {
        path_.push_front(get(boost::vertex_index, g_, v));
    }
};

struct null_add_path {
    template <class VertexDescriptor>
    void operator()(VertexDescriptor) {}
};

template <class Graph, class VertexDescriptor, class VertexIndex>
void success_test(const Graph& g,
                  VertexDescriptor start,
                  const std::deque<VertexIndex>& expected)
{
    std::deque<VertexIndex> path;

    add_path<std::deque<VertexIndex>, Graph> adder(path, g);
    if (!shand::graph::euler_path(g, start, adder)) {
        BOOST_TEST(false);
        return;
    }

    BOOST_TEST(path == expected);
}

template <class Graph, class VertexDescriptor>
void fail_test(const Graph& g, const VertexDescriptor& start)
{
    BOOST_TEST(!shand::graph::euler_path(g, start, null_add_path()));
}

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
    typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

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

    {
        const std::deque<int> expected = boost::assign::list_of(E)(B)(A)(C)(B)(D)(C)(E)(D);
        success_test(g, vertex(E, g), expected);
    }
    {
        const std::deque<int> expected = boost::assign::list_of(D)(B)(A)(C)(B)(E)(D)(C)(E);
        success_test(g, vertex(D, g), expected);
    }

    fail_test(g, vertex(A, g));
    fail_test(g, vertex(B, g));
    fail_test(g, vertex(C, g));

    return boost::report_errors();
}

