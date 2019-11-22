// Copyright 2019 Grama Nicolae
#include "FastGraph.hpp"

FastGraph::FastGraph(const uint nodeCount) : Graph(nodeCount) {
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

int32 FastGraph::Dijkstra(const uint source, const uint target) const {
    return 0;
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