// Copyright Grama Nicolae 2019
#include <queue>
#include "algo.h"

std::vector<std::vector<int32>> Johnson(
    const std::vector<std::vector<edge>> &graph) {
    // Costly operation, but is needed to restore the original graph
    std::vector<std::vector<edge>> auxAdjency =
        std::vector<std::vector<edge>>(graph);

    std::vector<std::vector<int32>> distances;

    // Bellman-Ford - to remove negative weights
    // Add the external node
    std::vector<int32> weight = std::vector<int32>(GlobalVariables::node_count + 1, INT32_MAX);

    // As we use the external node, the distance/weight to itself will be 0
    weight[GlobalVariables::node_count] = 0;

    // Add the auxiliary edges
    std::vector<edge> newNode;
    for (int node = 0; node < GlobalVariables::node_count; ++node) {
        newNode.push_back(std::make_pair(node, 0));
    }
    auxAdjency.push_back(newNode);

    // Relax edges
    bool changed = false;
    for (int iteration = 0; iteration < GlobalVariables::node_count; ++iteration) {
        // For each edge (including the auxiliary ones)
        for (int source = 0; source < GlobalVariables::node_count + 1; ++source) {
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
    for (int source = 0; source < GlobalVariables::node_count + 1; ++source) {
        for (auto &edge : auxAdjency[source]) {
            if (weight[source] + edge.second < weight[edge.first]) {
                // Return a "valid" response
                return std::vector<std::vector<int32>>(0);
            }
        }
    }

    // Update all distances in the graph
    for (int source = 0; source < GlobalVariables::node_count; ++source) {
        for (auto &edge : auxAdjency[source]) {
            edge.second = edge.second + weight[source] - weight[edge.first];
        }
    }

    // Dijkstra - to compute the distances
    // Pick each node as a source for pathfinding
    for (int source = 0; source < GlobalVariables::node_count; ++source) {
        // Distance to the other nodes
        std::vector<int32> distance = std::vector<int32>(GlobalVariables::node_count, INT32_MAX);
        std::vector<int> previous = std::vector<int>(GlobalVariables::node_count, UINT32_MAX);
        distance[source] = 0;

        // Start from source
        std::queue<int> toVisit;
        std::vector<bool> visited = std::vector<bool>(GlobalVariables::node_count, false);
        toVisit.push(source);

        while (!toVisit.empty()) {
            int cNode = toVisit.front();

            // Add unvisited nodes to the graph & update distances
            for (auto &neighbour : graph[cNode]) {
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
        for (int node = 0; node < GlobalVariables::node_count; ++node) {
            if (node != source) {
                int curr = node;
                int prev = previous[node];
                int32 cost = 0;

                // While we have a predecesor, add the cost of the intermediary
                // links
                while (prev != INT32_MAX) {
                    for (auto &elem : graph[prev]) {
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