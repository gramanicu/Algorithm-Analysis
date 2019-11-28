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
        neighbours.push_back(link);
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
    std::vector<std::vector<int32>> distances = std::vector<std::vector<int32>>(
        _nodeCount, std::vector<int32>(_nodeCount, INT32_MAX));

    // Create the initial matrix (adjency matrix)
    for (uint i = 0; i < _nodeCount; ++i) {
        distances[i][i] = 0;
    }

    for (uint source = 0; source < _nodeCount; ++source) {
        for (auto &target : adjency[source]) {
            distances[source][target.first] = target.second;
        }
    }

    for (uint inter = 0; inter < _nodeCount; ++inter) {
        for (uint source = 0; source < _nodeCount; ++source) {
            for (uint target = 0; target < _nodeCount; ++target) {
                int32 newDistance =
                    distances[source][inter] + distances[inter][target];

                // Keep the sum infinite, if that is the case
                if (distances[source][inter] == INT32_MAX ||
                    distances[inter][target] == INT32_MAX) {
                    newDistance = INT32_MAX;
                }

                if (newDistance < distances[source][target]) {
                    distances[source][target] = newDistance;
                }
            }
        }
    }

    return distances;
}

std::vector<std::vector<int32>> SmallGraph::Johnson() const {
    // Costly operation, but is needed to restore the original graph
    std::vector<std::vector<std::pair<uint, int32>>> auxAdjency =
        std::vector<std::vector<std::pair<uint, int32>>>(adjency);
    std::vector<std::vector<int32>> distances;

    // Bellman-Ford - to remove negative weights
    // Add the external node
    std::vector<int32> weight = std::vector<int32>(_nodeCount + 1, INT32_MAX);

    // As we use the external node, the distance/weight to itself will be 0
    weight[_nodeCount] = 0;

    // Add the auxiliary edges
    std::vector<std::pair<uint, int32>> newNode;
    for (uint node = 0; node < _nodeCount; ++node) {
        newNode.push_back(std::make_pair(node, 0));
    }
    auxAdjency.push_back(newNode);

    // Relax edges
    bool changed = false;
    for (uint iteration = 0; iteration < _nodeCount; ++iteration) {
        // For each edge (including the auxiliary ones)
        for (uint source = 0; source < _nodeCount + 1; ++source) {
            for (auto &edge : auxAdjency[source]) {
                if (weight[source] + edge.second < weight[edge.first]) {
                    weight[edge.first] = weight[source] + edge.second;
                    changed = true;
                }
            }
        }

        // If it didn't relax, stop the algorithm
        if (!changed) {
            break;
        }
    }

    // Check for negative weights
    for (uint source = 0; source < _nodeCount + 1; ++source) {
        for (auto &edge : auxAdjency[source]) {
            if (weight[source] + edge.second < weight[edge.first]) {
                // The graph contains negative cycles
                std::cerr << "Graph contains negative cycles\n";

                // Return a valid response
                return FloydWarshall();
            }
        }
    }

    // Update all distances in the graph
    for (uint source = 0; source < _nodeCount; ++source) {
        for (auto &edge : auxAdjency[source]) {
            edge.second = edge.second + weight[source] - weight[edge.first];
        }
    }

    // Dijkstra - to compute the distances
    // Pick each node as a source for pathfinding
    for (uint source = 0; source < _nodeCount; ++source) {
        // Distance to the other nodes
        std::vector<int32> distance = std::vector<int32>(_nodeCount, INT32_MAX);
        std::vector<uint> previous = std::vector<uint>(_nodeCount, UINT32_MAX);
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
                    previous[neighbour.first] = cNode;
                }
            }

            // The node was visited
            toVisit.pop();
        }

        // Compute the real distance (by using the original costs and "walking
        // back")
        for (uint node = 0; node < _nodeCount; ++node) {
            if (node != source) {
                uint curr = node;
                uint prev = previous[node];
                int32 cost = 0;

                // While we have a predecesor, add the cost of the intermediary
                // links
                while (prev != UINT32_MAX) {
                    for (auto &elem : adjency[prev]) {
                        if (elem.first == curr) {
                            cost += elem.second;
                            break;
                        }
                    }

                    // Go back a node
                    curr = prev;
                    prev = previous[curr];
                }

                if (cost == 0 && source != node) {
                    cost = INT32_MAX;
                }

                distance[node] = cost;
            }
        }

        distances.push_back(distance);
    }

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