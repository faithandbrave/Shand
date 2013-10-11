#ifndef SHAND_GRAPH_EULER_PATH_INCLUDE
#define SHAND_GRAPH_EULER_PATH_INCLUDE

// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <map>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>

namespace shand { namespace graph {

template <class Graph>
inline bool
    has_euler_path(const Graph& g,
                   typename boost::graph_traits<Graph>::vertex_descriptor s)
{
    typedef boost::graph_traits<Graph> traits;
    typedef typename traits::vertex_descriptor vertex_desc;
    typedef typename traits::degree_size_type degree_size_type;

    std::size_t odd = 0;
    BOOST_FOREACH (const vertex_desc& v, vertices(g)) {
        const degree_size_type size = out_degree(v, g);
        if (size % 2 == 1)
            ++odd;
    }
    return (odd == 0 || (odd == 2 && out_degree(s, g) % 2 == 1));
}

namespace euler_detail {

template <class Graph, class Matrix, class UnaryFunction>
inline void visit(const Graph& g,
                 Matrix& matrix,
                 typename boost::graph_traits<Graph>::vertex_descriptor s,
                 UnaryFunction f,
                 std::size_t& path_size)
{
    typedef typename boost::graph_traits<Graph>::edge_descriptor edge_desc;

    BOOST_FOREACH (const edge_desc& e, out_edges(s, g)) {
        if (matrix[std::make_pair(source(e, g), target(e, g))] >= 0) {
            --matrix[std::make_pair(source(e, g), target(e, g))];
            --matrix[std::make_pair(target(e, g), source(e, g))];
            visit(g, matrix, target(e, g), f, path_size);
        }
    }
    f(s);
    ++path_size;
}

// Eulerian tour for undirected graph.
// Implementation use Hierholzer's algorithm.
// Requires : Graph is VertexAndEdgeListGraph
// Complexity : O(E)
// Parameters : `g` is target graph object.
//              `s` is start vertex for tour
//              `f` is unary function object. the function call when discover vertex. Vertex order is reverse.
// Returns : `true` if find eulerian path, and `false` otherwise.
template <class Graph, class UnaryFunction>
inline bool euler_path(const Graph& g,
                       typename boost::graph_traits<Graph>::vertex_descriptor s,
                       UnaryFunction f,
                       boost::undirected_tag)
{
    BOOST_CONCEPT_ASSERT(( boost::VertexAndEdgeListGraphConcept<Graph> ));

    if (!has_euler_path(g, s))
        return false;

    typedef typename boost::graph_traits<Graph>::vertex_descriptor vertex_desc;
    std::map<std::pair<vertex_desc, vertex_desc>, int> matrix;

    std::size_t path_size = 0;
    visit(g, matrix, s, f, path_size);

    return path_size == num_edges(g) + 1;
}

} // namespace euler_detail

template <class Graph, class UnaryFunction>
inline bool euler_path(const Graph& g,
                       typename boost::graph_traits<Graph>::vertex_descriptor s,
                       UnaryFunction f)
{
    typedef typename boost::graph_traits<Graph>::directed_category Cat;
    return euler_detail::euler_path(g, s, f, Cat());
}

}} // namespace shand::graph

#endif // SHAND_GRAPH_EULER_PATH_INCLUDE

