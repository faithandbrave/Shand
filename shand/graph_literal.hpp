#ifndef SHAND_GRAPH_LITERAL_INCLUDE
#define SHAND_GRAPH_LITERAL_INCLUDE

// Graph Literal EDSL
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <shand/fusion/adjacency_for_each.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace shand {

struct graph_converter {
    typedef std::vector<std::pair<int, int> > edges_type;

    edges_type edges;

    edges_type::iterator begin() { return edges.begin(); }
    edges_type::const_iterator begin() const { return edges.begin(); }

    edges_type::iterator end() { return edges.end(); }
    edges_type::const_iterator end() const { return edges.end(); }
};

template <class>
struct is_vertex_type : boost::mpl::false_ {};

template <class Seq, class T>
typename boost::lazy_enable_if<
    boost::fusion::traits::is_sequence<Seq>,
    boost::fusion::result_of::as_vector<
        typename boost::fusion::result_of::push_back<const Seq, T>::type
    >
>::type
    operator>=(const Seq& seq, const T& x)
{
    return boost::fusion::as_vector(boost::fusion::push_back(seq, x));
}

template <class T, class U>
typename boost::disable_if<
    boost::fusion::traits::is_sequence<T>,
    boost::fusion::vector<T, U>
>::type
    operator>=(const T& a, const U& b)
{
    return boost::fusion::make_vector(a, b);
}

template <class Dest>
struct push_backer {
    Dest& dest;

    push_backer(Dest& dest) : dest(dest) {}

    template <class Seq>
    void operator()(const Seq& seq) const
    {
        dest.push_back(std::make_pair(boost::fusion::at_c<0>(seq), boost::fusion::at_c<1>(seq)));
    }
};

template <class Vertices, class Edges>
void vertices_to_edges(const Vertices& vertices, Edges& edges)
{
    shand::fusion::adjacency_for_each(vertices, push_backer<Edges>(edges));
}

template <class LSeq, class RSeq>
typename boost::enable_if<
    boost::fusion::traits::is_sequence<LSeq>,
    graph_converter
>::type
    operator&(const LSeq& a, const RSeq& b)
{
    graph_converter g;
    vertices_to_edges(a, g.edges);
    vertices_to_edges(b, g.edges);

    return g;
}


template <class T>
struct vertex_t {
    T value;

    typedef T value_type;

    vertex_t() {}
    vertex_t(const T& value) : value(value) {}

    operator T() const
    {
        return value;
    }
};

template <class T>
vertex_t<T> vertex(T x)
{
    return vertex_t<T>(x);
}

template <class T>
struct is_vertex_type<vertex_t<T> > : boost::mpl::true_ {};

} // namespace shand

#endif // SHAND_GRAPH_LITERAL_INCLUDE

