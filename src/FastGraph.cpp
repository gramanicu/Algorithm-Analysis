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

    for (uint i = 0; i < _nodeCount; ++i) {
        if (adjency[source][i] != 0) {
            neighbours.push_back(i);
        }
    }

    return neighbours;
}

std::vector<std::vector<int32>> FastGraph::Dijkstra() const {
    std::vector<std::vector<int32>> distances;

    // Pick each node as a source for pathfinding
    for (uint source = 0; source < _nodeCount; ++source) {
        // Distance to the other nodes
        std::vector<int32> distance = std::vector<int32>(_nodeCount, INT32_MAX);
        distance[source] = 0;

        // Start from source
        std::queue<uint> toVisit;
        std::vector<bool> visited = std::vector<bool>(_nodeCount, false);
        toVisit.push(source);

        while (!toVisit.empty()) {
            uint cNode = toVisit.front();

            // Add unvisited nodes to the graph & update distances
            for (auto &neighbour : neighbours(cNode)) {
                if (visited[neighbour] == false) {
                    toVisit.push(neighbour);
                    visited[neighbour] = true;
                }

                // The distance from the current node to the neighbour
                int32 currentDistance =
                    distance[cNode] + adjency[cNode][neighbour];

                // If the distance is shorter, update the distance
                if (currentDistance < distance[neighbour]) {
                    distance[neighbour] = currentDistance;
                }
            }

            // The node was visited
            toVisit.pop();
        }

        distances.push_back(distance);
    }

    return distances;
}

std::vector<std::vector<int32>> FastGraph::FloydWarshall() const {
    std::vector<std::vector<int32>> distances = adjency;

    // Adjust the graph for the algorithm (infinite distance between unlinked nodes)
    for(auto &row : distances) {
        for(auto &elem : row) {
            if(elem == 0) {
                elem = INT32_MAX;
            }
        }
    }

    // No loops (0 distance to the node itself)
    for (uint i = 0 ; i < _nodeCount; ++i) {
        distances[i][i] = 0;
    }
    
    for (uint inter = 0; inter < _nodeCount; ++inter) {
        for(uint source = 0 ; source < _nodeCount; ++source) {
            for (uint target = 0; target < _nodeCount; ++target) {
                int32 newDistance = distances[source][inter] + distances[inter][target];

                // Keep the sum infinite, if that is the case
                if(distances[source][inter] == INT32_MAX || distances[inter][target] == INT32_MAX) {
                    newDistance = INT32_MAX;
                }

                if(newDistance < distances[source][target]) {
                    distances[source][target] = newDistance;
                }
            }
        }
    }

    return distances;
}

std::vector<std::vector<int32>> FastGraph::Johnson() const {
    std::vector<std::vector<int32>> distances;
    return distances;
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