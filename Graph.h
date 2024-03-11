#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <list>
#include <vector>
#include <limits>

static const short NIL = -1;
static const double INF = std::numeric_limits<double>::infinity();

class Graph {
public:
    Graph() = default;

    void addEdge(int source, int dest, double weight = 1);
    void setEdgeList();
    void erase();
    int getEdgeCount() const;
    const std::vector<int>& getEdges(int i) const;

private:
    struct Edge {
        int dest;
        double weight;
        Edge(int d, double w) : dest(d), weight(w) {}
    };

    struct NodeProperties {
        double dist;
        int parent;
    };

    using EdgeList = std::list<Edge>;
    using AdjacencyMap = std::map<int, EdgeList>;
    using PropertyMap = std::map<int, NodeProperties>;

    std::vector<std::vector<int>> edgeList;
    AdjacencyMap adj;
    PropertyMap prop;
};

#endif /* GRAPH_H */
