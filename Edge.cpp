#include "Edge.h"

Edge::Edge() {
    toNodeId = 0;
    version = 0;
    distance = 0;
}

Edge::Edge(int to, int v, int d) {
    toNodeId = to;
    version = v;
    distance = d;
}

bool Edge::operator<(const Edge& other) const {
    
    if(version == other.version)
    {
        if(distance == other.distance)
        {
            return false; 
        }
        return this -> distance < other.distance;
    }
    return this -> version < other.version;
    
    return false;
}