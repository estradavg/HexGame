#include "Graph.h"

// Adds an undirected edge between source and dest with a defined weight.
void Graph::addEdge(int source, int dest, double weight) 
{
    adj[source].emplace_back(dest, weight);
    adj[dest].emplace_back(source, weight);

    prop[source] = {INF, NIL};
    prop[dest] = {INF, NIL};
}

void Graph::setEdgeList() 
{
    edgeList.resize(adj.size() + 1);
    for (const auto& entry : adj) 
    {
        edgeList[entry.first].reserve(entry.second.size() + 1);
        for (const auto& edge : entry.second) 
        {
            edgeList[entry.first].push_back(edge.dest);
        }
    }
}

const std::vector<int>& Graph::getEdges(int i) const 
{
    return edgeList[i];
}

// Erases all nodes in the graph.
void Graph::erase() {
    adj.clear();
    prop.clear();
}

// Returns the number of edges in the Graph.
int Graph::getEdgeCount() const 
{
    int count = 0;
    for (const auto& entry : adj) 
    {
        count += entry.second.size();
    }
    return count / 2;
}
