// Copyright Grama Nicolae 2019
#include "algo.h"

int GlobalVariables::edge_count = 0;
bool GlobalVariables::has_negatives = false;
int GlobalVariables::node_count = 0;
std::vector<std::vector<int32>> GlobalVariables::last_output =
    std::vector<std::vector<int32>>(0);

std::vector<std::vector<int32>> shortest_path_all(
    const std::vector<std::vector<edge>>& graph) {
    if(GlobalVariables::has_negatives) {
        GlobalVariables::last_output = Johnson(graph);
    } else {
        GlobalVariables::last_output = Dijkstra(graph);
    }

    return GlobalVariables::last_output;
}