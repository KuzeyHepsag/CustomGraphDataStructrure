#include "Graph.h"

Graph::Graph(int n) {
    adjacencyList.resize(n);
    numNodes = n;
}

void Graph::addEdge(int from, int to, int version, int distance) {
    
    for(std::vector<Edge>::iterator it = adjacencyList[from].begin(); it != adjacencyList[from].end(); it++)
    {
        if(it -> toNodeId == to)
        {
            if(version > (it -> version))
            {
                return ;
            }
            if(distance> (it -> version))
                return ;
            it -> version = version;
            it -> distance = distance;
            return ;
        }
    }
    adjacencyList[from].push_back(Edge(to,version,distance));
}

const std::vector<Edge>& Graph::getNeighbors(int nodeId) const {
    return adjacencyList[nodeId];
}

int Graph::getNumNodes() const {
    return numNodes;
}