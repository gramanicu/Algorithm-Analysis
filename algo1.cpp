#include <iostream>
#include <queue>
#include "algo.h"

std::vector<std::vector<int32>> Dijkstra(
    const std::vector<std::vector<edge>>& graph) {
    std::vector<std::vector<int32>> distances;

    // Pick each node as a source for pathfinding
    for (int source = 0; source < GlobalVariables::node_count; ++source) {
        // Distance to the other nodes
        std::vector<int32> distance =
            std::vector<int32>(GlobalVariables::node_count, INT32_MAX);
        distance[source] = 0;

        // Start from source
        std::queue<int> toVisit;
        std::vector<bool> visited =
            std::vector<bool>(GlobalVariables::node_count, false);
        toVisit.push(source);

        while (!toVisit.empty()) {
            int cNode = toVisit.front();

            // Add unvisited nodes to the graph & update distances
            for (auto& neighbour : graph[cNode]) {
                if (visited[neighbour.first] == false) {
                    toVisit.push(neighbour.first);
                    visited[neighbour.first] = true;
                }

                // The distance from the current node to the neighbour
                int currentDistance = distance[cNode] + neighbour.second;

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