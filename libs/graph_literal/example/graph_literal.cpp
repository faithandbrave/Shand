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
    const shand::graph_converter edges = (
                vertex(A) >= vertex(B) &
                vertex(A) >= vertex(C) >= vertex(D)
            );

    graph_type g(edges.begin(), edges.end(), N);

    std::ofstream file("test.dot");
    boost::write_graphviz(file, g, boost::make_label_writer(name.c_str()));
}
