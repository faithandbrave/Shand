#ifndef SHAND_GRAPH_EULER_PATH_INCLUDE
#define SHAND_GRAPH_EULER_PATH_INCLUDE

// Copyright Akira Takahashi 2012
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace shand { namespace graph {

template <class Graph>
inline boost::optional<std::size_t>
    is_euler_graph(const Graph& g,
                   typename boost::graph_traits<Graph>::vertex_descriptor s)
{
    typedef boost::graph_traits<Graph> traits;
    typedef typename traits::vertex_descriptor vertex_desc;
    typedef typename traits::degree_size_type degree_size_type;

    std::size_t odd = 0;
    std::size_t m = 0;
    BOOST_FOREACH (const vertex_desc& v, boost::vertices(g)) {
        const degree_size_type size = boost::degree(v, g);
        if (size % 2 == 1) ++odd;
        m += size;
    }
    m /= 2;
    if (!(odd == 0 || (odd == 2 && boost::degree(s, g) % 2 == 1)))
        return boost::none;
    return m;
}

namespace euler_detail {

template <class Graph, class Adj, class UnaryFunction>
inline void visit(const Graph& g,
                 Adj& adj,
                 typename boost::graph_traits<Graph>::vertex_descriptor s,
                 UnaryFunction f,
                 std::size_t& path_size)
{
    typedef boost::graph_traits<Graph> traits;
    typedef typename traits::vertex_descriptor vertex_desc;
    typedef typename traits::edge_descriptor edge_desc;

    BOOST_FOREACH (const edge_desc& e, boost::out_edges(s, g)) {
        if (adj[boost::source(e, g)][boost::target(e, g)] > 0) {
            --adj[boost::source(e, g)][boost::target(e, g)];
            --adj[boost::target(e, g)][boost::source(e, g)];
            visit(g, adj, boost::target(e, g), f, path_size);
        }
    }
    f(s);
    ++path_size;
}

// Eulerian tour for undirected graph.
// Implementation use Hierholzer's algorithm.
// Requires : Graph is IncidenceGraph
// Complexity : O(E)
// Returns : `true` if find eulerian path, and `false` otherwise.
template <class Graph, class UnaryFunction>
inline bool euler_path(const Graph& g,
                       typename boost::graph_traits<Graph>::vertex_descriptor s,
                       UnaryFunction f,
                       boost::undirected_tag)
{
    boost::optional<std::size_t> m = is_euler_graph(g, s);
    if (!m) return false;

    typedef boost::graph_traits<Graph> traits;
    typedef typename traits::vertex_descriptor vertex_desc;
    typedef typename traits::edge_descriptor edge_desc;

    const std::size_t n = boost::num_vertices(g);
    std::vector<std::vector<int> > adj(n, std::vector<int>(n));
    BOOST_FOREACH (const edge_desc& e, boost::edges(g)) {
        ++adj[boost::source(e, g)][boost::target(e, g)];
        ++adj[boost::target(e, g)][boost::source(e, g)];
    }

    std::size_t path_size = 0;
    visit(g, adj, s, f, path_size);

    return path_size == m.get() + 1;
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

