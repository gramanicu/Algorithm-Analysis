#include "algo.h"

std::vector<std::vector<int32>> FloydWarshall(
    const std::vector<std::vector<edge>>& graph) {
    std::vector<std::vector<int32>> distances = std::vector<std::vector<int32>>(
        node_count, std::vector<int32>(node_count, INT32_MAX));

    // Create the initial matrix (adjency matrix)
    for (int i = 0; i < node_count; ++i) {
        distances[i][i] = 0;
    }

    for (int source = 0; source < node_count; ++source) {
        for (auto& target : graph[source]) {
            distances[source][target.first] = target.second;
        }
    }

    for (int inter = 0; inter < node_count; ++inter) {
        for (int source = 0; source < node_count; ++source) {
            for (int target = 0; target < node_count; ++target) {
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