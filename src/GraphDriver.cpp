// Copyright 2019 Grama Nicolae
#include "GraphDriver.hpp"

#define DENSITY_THRESHOLD 1.5f

Graph* GraphDriver::graph = nullptr;
bool GraphDriver::hasNegatives = false;
int GraphDriver::lastEdges = 0;
int GraphDriver::lastNodes = 0;

GraphDriver::GraphDriver() {}

GraphDriver::~GraphDriver() { delete graph; }

void GraphDriver::readData(std::istream& input) {
    uint nodeCount, edgeCount = 0;

    input >> nodeCount;
    input >> edgeCount;

    double graphDensity;

    graphDensity = 2.0 * double(edgeCount) /
                   (double(nodeCount) * (double(nodeCount) - 1.0f));

    if (graphDensity < DENSITY_THRESHOLD) {
        graph = new SmallGraph(nodeCount);
        // std::cout << "Sparse/Small Graph\n";
    } else {
        graph = new FastGraph(nodeCount);
        // std::cout << "Dense/Fast Graph\n";
    }

    lastEdges = edgeCount;
    lastNodes = nodeCount;

    for (uint i = 0; i < edgeCount; ++i) {
        uint source, target;
        int32 cost;

        input >> source >> target >> cost;

        if (cost < 0) {
            hasNegatives = true;
        }

        // Because the input has nodes 1 -> N and the graph uses 0 -> N-1
        // the node id's are changed before they are added
        graph->link(source - 1, target - 1, cost);
    }
}


void GraphDriver::setData(const std::vector<std::vector<edge>>& othergraph) {
    graph = new SmallGraph(othergraph.size());

    lastNodes = othergraph.size();
    lastEdges = 0;
    for(int i = 0 ; i < lastNodes ; ++i) {

        lastEdges += othergraph[i].size();

        for(auto& edge : othergraph[i]) {
            if(edge.second < 0) {
                hasNegatives = true;
            }

            graph->link(i, edge.first, edge.second);
        }
    }
}

std::vector<std::vector<int32>> GraphDriver::Dijkstra() {
    return graph->Dijkstra();
}

std::vector<std::vector<int32>> GraphDriver::FloydWarshall() {
    return graph->FloydWarshall();
}

std::vector<std::vector<int32>> GraphDriver::Johnson() {
    return graph->Johnson();
}

std::vector<std::vector<int32>> GraphDriver::Best() {
    if (!hasNegatives) {
        return graph->Dijkstra();
    }

    return graph->Johnson();
}