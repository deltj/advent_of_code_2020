/**
 * Figure out some baggage
 */
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/reverse_graph.hpp>

struct Vertex
{
    std::string name;
};

struct Edge
{
    int num;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, Vertex, Edge> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
typedef boost::graph_traits<Graph>::edge_descriptor EdgeDescriptor;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;

int sumDescendantWeights(const VertexDescriptor &v, Graph &g)
{
    int sum = 0;

    boost::graph_traits<Graph>::out_edge_iterator ei, end;
    for(boost::tie(ei, end) = boost::out_edges(v, g); ei != end; ++ei)
    {
        //std::cout << g[*ei].num << " " << g[target(*ei, g)].name << std::endl;
        sum += g[*ei].num;

        sum += g[*ei].num * sumDescendantWeights(target(*ei, g), g);
    }

    return sum;
}

std::vector<Vertex> findDescendants(const VertexDescriptor &v, Graph &g)
{
    std::vector<Vertex> result;

    boost::graph_traits<Graph>::out_edge_iterator ei, end;
    for(boost::tie(ei, end) = boost::out_edges(v, g); ei != end; ++ei)
    {
        //std::cout << g[target(*ei, g)].name << std::endl;
        result.push_back(g[target(*ei, g)]);

        std::vector<Vertex> descendants = findDescendants(target(*ei, g), g);
        result.insert(result.end(), descendants.begin(), descendants.end());
    }

    return result;
}

VertexIterator findVertex(const std::string &name, Graph &g)
{
    VertexIterator vi, end;
    for(boost::tie(vi, end) = boost::vertices(g); vi != end; ++vi)
    {
        if(g[*vi].name.compare(name) == 0)
        {
            return vi;
        }
    }
    return end;
}

VertexDescriptor findOrAddVertex(const std::string &name, Graph &g)
{
    VertexIterator vi = findVertex(name, g);
    VertexIterator end = boost::vertices(g).second;
    if(vi != end)
    {
        return *vi;
    }

    //  Vertex wasn't found, add it

    Vertex v;
    v.name = name;

    return boost::add_vertex(v, g);
}

void usage()
{
    std::cout << "day7 <input.txt>" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        usage();
        return EXIT_FAILURE;
    }

    Graph g;

    std::cout << "processing input" << std::endl;
    std::ifstream ifs(argv[1], std::ifstream::in);
    std::string line;
    while(std::getline(ifs, line))
    {
        //std::cout << line << std::endl;

        std::vector<std::string> lineTokens;
        boost::split_regex(lineTokens, line, boost::regex(" contain "));

        if(lineTokens.size() == 2)
        {
            const std::string name = boost::regex_replace(lineTokens[0], boost::regex(" bags"), "");
            //std::cout << name << std::endl;

            VertexDescriptor v1 = findOrAddVertex(name, g);

            if(lineTokens[1].compare("no other bags.") == 0)
            {
                //  This bag contains no other bags, nothing to do
                //std::cout << "** nothing to do" << std::endl;
            }
            else
            {
                std::vector<std::string> contentsTokens;
                boost::split(contentsTokens, lineTokens[1], boost::is_any_of(",."));
                for(std::vector<std::string>::const_iterator it=contentsTokens.begin(); it!=contentsTokens.end(); ++it)
                {
                    std::string bagStr = boost::trim_copy(*it);

                    if(bagStr.length() > 0)
                    {
                        //std::cout << "*** " << bagStr << std::endl;
                        
                        std::vector<std::string> bagTokens;
                        boost::split(bagTokens, bagStr, boost::is_any_of(" "));
                        if(bagTokens.size() == 4)
                        {
                            const int num = boost::lexical_cast<int>(bagTokens[0]);
                            std::stringstream ss;
                            ss << bagTokens[1];
                            ss << " ";
                            ss << bagTokens[2];
                            //std::cout << ss.str() << std::endl;

                            VertexDescriptor v2 = findOrAddVertex(ss.str(), g);

                            Edge e;
                            e.num = num;
                            boost::add_edge(v1, v2, e, g);
                        }
                    }

                }
            }
        }
    }

    std::cout << "discovering descendants" << std::endl;

    //  Make a reversed version of the digraph created above
    //Graph rg;
    //boost::copy_graph(boost::make_reverse_graph(g), rg);

    VertexIterator sg = findVertex("shiny gold", g);
    int sum = sumDescendantWeights(*sg, g);
    std::cout << "sum: " << sum << std::endl;

    std::ofstream dotfile("graph.dot");
    boost::write_graphviz(dotfile, g,
            boost::make_label_writer(boost::get(&Vertex::name, g)),
            boost::make_label_writer(boost::get(&Edge::num, g)));


    ifs.close();
}
