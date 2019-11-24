// Copyright 2019 Grama Nicolae
#include "FastGraph.hpp"

FastGraph::FastGraph(const uint nodeCount) : _nodeCount(nodeCount) {
    adjency = std::vector<std::vector<int32>>(nodeCount,
                                              std::vector<int32>(nodeCount, 0));
}

FastGraph::~FastGraph() {}

void FastGraph::link(const uint source, const uint target, const int32 cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    adjency[source][target] = cost;
}

void FastGraph::linkBoth(const uint source, const uint target,
                         const int32 cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    adjency[source][target] = cost;
    adjency[target][source] = cost;
}

void FastGraph::unlink(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;
    adjency[source][target] = 0;
}

void FastGraph::unlinkBoth(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;
    adjency[source][target] = 0;
    adjency[target][source] = 0;
}

int32 FastGraph::nodesCount() const { return _nodeCount; }

std::vector<uint> FastGraph::neighbours(const uint source) const {
    std::vector<uint> neighbours;
    
    for (uint i = 0 ; i < _nodeCount ; ++i) {
        if(adjency[source][i] != 0) {
            neighbours.push_back(i);
        }   
    }
    
    return neighbours;
}

int32 FastGraph::Dijkstra(const uint source, const uint target) const {
    // Distance to the other nodes
    std::vector<int32> distance = std::vector<int32>(_nodeCount, INT32_MAX);
    distance[source] = 0;

    // Start from source
    std::queue<uint> toVisit;
    std::vector<bool> visited = std::vector<bool>(_nodeCount, false);
    toVisit.push(source);

    while(!toVisit.empty()) {
        uint cNode = toVisit.front();

        // Add unvisited nodes to the graph & update distances
        for(auto &neighbour : neighbours(cNode)) {
            if(visited[neighbour] == false) {
                toVisit.push(neighbour);
                visited[neighbour] = true;
            }

            // The distance from the current node to the neighbour
            int32 currentDistance = distance[cNode] + adjency[cNode][neighbour];

            // If the distance is shorter, update the distance            
            if(currentDistance < distance[neighbour]) {
                distance[neighbour] = currentDistance;
            }
        }

        // The node was visited
        toVisit.pop();
    }

    return distance[target];
}

int32 FastGraph::FloydWarshall(const uint source, const uint target) const {
    return 0;
}

int32 FastGraph::Johnson(const uint source, const uint target) const {
    return 0;
}

void FastGraph::print(std::ostream &output) const {
    for (auto &row : adjency) {
        for (auto &elem : row) {
            output << elem << " ";
        }
        output << "\n";
    }
}

bool FastGraph::nodeIDValid(const uint first, const uint second) const {
    if (first < _nodeCount) {
        if (second < _nodeCount) {
            if (first != second) {
                return true;
            }
        }
    }
    return false;
}