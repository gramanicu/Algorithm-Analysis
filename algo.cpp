#include "algo.h"

std::vector<std::vector<int32>> shortest_path_all(
    const std::vector<std::vector<edge>>& graph) {
        // if(has_negatives) {
            return Dijkstra(graph);
        // } else {
            // return Johnson(graph);
        // }
}

std::vector<std::pair<int, int>> neighbours(
    const int source, const std::vector<std::vector<edge>>& graph) {
    std::vector<std::pair<int, int>> neighbours;

    for (auto &link : graph[source]) {
        neighbours.push_back(link);
    }

    return neighbours;
}