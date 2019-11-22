// Copyright 2019 Grama Nicolae
#include "SmallGraph.hpp"

SmallGraph::SmallGraph(const uint nodeCount) : Graph(nodeCount) {
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

int32 SmallGraph::Dijkstra(const uint source, const uint target) const {
    return 0;
}

int32 SmallGraph::FloydWarshall(const uint source, const uint target) const {
    return 0;
}

int32 SmallGraph::Johnson(const uint source, const uint target) const {
    return 0;
}

void SmallGraph::print(std::ostream &output) const {
    for (uint i = 0; i < adjency.size(); ++i) {
        for (auto &node : adjency[i]) {
            output << i << " -> " << node.first << " : " << node.second << "\n";
        }
    }
}