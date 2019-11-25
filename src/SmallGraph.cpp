// Copyright 2019 Grama Nicolae
#include "SmallGraph.hpp"

SmallGraph::SmallGraph(const uint nodeCount) : _nodeCount(nodeCount) {
    std::pair<uint, int32> emptyPair = std::make_pair(0, 0);
    adjency = std::vector<std::vector<std::pair<uint, int32>>>(
        nodeCount, std::vector<std::pair<uint, int32>>(0, emptyPair));
}

SmallGraph::~SmallGraph() {}

bool SmallGraph::edgeExist(const uint source, const uint target) const {
    for (auto &edge : adjency[source]) {
        if (edge.first == target) {
            return true;
        }
    }
    return false;
}

void SmallGraph::link(const uint source, const uint target, const int32 cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    if (edgeExist(source, target)) return;

    adjency[source].push_back(std::make_pair(target, cost));
}

void SmallGraph::linkBoth(const uint source, const uint target,
                          const int32 cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    if (edgeExist(source, target)) return;

    adjency[source].push_back(std::make_pair(target, cost));

    if (edgeExist(target, source)) return;
    adjency[target].push_back(std::make_pair(source, cost));
}

void SmallGraph::unlink(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;

    for (auto it = adjency[source].begin(); it != adjency[source].end(); ++it) {
        if (it->first == target) {
            adjency[source].erase(it);
            return;
        }
    }
}

void SmallGraph::unlinkBoth(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;

    for (auto it = adjency[source].begin(); it != adjency[source].end(); ++it) {
        if (it->first == target) {
            adjency[source].erase(it);
            break;
        }
    }

    for (auto it = adjency[target].begin(); it != adjency[target].end(); ++it) {
        if (it->first == source) {
            adjency[target].erase(it);
            break;
        }
    }
}

int32 SmallGraph::nodesCount() const { return _nodeCount; }

std::vector<std::pair<uint, int32>> SmallGraph::neighbours(
    const uint source) const {
    std::vector<std::pair<uint, int32>> neighbours;

    for (auto &link : adjency[source]) {
        if (link.second != 0) {
            neighbours.push_back(link);
        }
    }

    return neighbours;
}

std::vector<std::vector<int32>> SmallGraph::Dijkstra() const {
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
                if (visited[neighbour.first] == false) {
                    toVisit.push(neighbour.first);
                    visited[neighbour.first] = true;
                }

                // The distance from the current node to the neighbour
                int32 currentDistance = distance[cNode] + neighbour.second;

                // If the distance is shorter, update the distance
                if (currentDistance < distance[neighbour.first]) {
                    distance[neighbour.first] = currentDistance;
                }
            }

            // The node was visited
            toVisit.pop();
        }

        distances.push_back(distance);
    }
    return distances;
}

std::vector<std::vector<int32>> SmallGraph::FloydWarshall() const {
    std::vector<std::vector<int32>> distances;
    return distances;
}

std::vector<std::vector<int32>> SmallGraph::Johnson() const {
    std::vector<std::vector<int32>> distances;
    return distances;
}

void SmallGraph::print(std::ostream &output) const {
    for (uint i = 0; i < adjency.size(); ++i) {
        for (auto &node : adjency[i]) {
            output << i << " -> " << node.first << " : " << node.second << "\n";
        }
    }
}

bool SmallGraph::nodeIDValid(const uint first, const uint second) const {
    if (first < _nodeCount) {
        if (second < _nodeCount) {
            if (first != second) {
                return true;
            }
        }
    }
    return false;
}