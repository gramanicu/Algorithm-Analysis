// Copyright 2019 Grama Nicolae
#include "GraphDriver.hpp"

#define DENSITY_THRESHOLD 1.5f

std::ostream& operator<<(std::ostream& output,
                         const std::vector<std::vector<int32>> matrix) {
    for (auto& row : matrix) {
        for (auto& elem : row) {
            if (elem == INT32_MAX) {
                output << "inf ";
            } else {
                output << elem << " ";
            }
        }
        output << "\n";
    }
    return output;
}

Graph* GraphDriver::graph = nullptr;

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
        std::cout << "Sparse/Small Graph\n";
    } else {
        graph = new FastGraph(nodeCount);
        std::cout << "Dense/Fast Graph\n";
    }

    for (uint i = 0; i < edgeCount; ++i) {
        uint source, target;
        int32 cost;

        input >> source >> target >> cost;

        // Because the input has nodes 1 -> N and the graph uses 0 -> N-1
        // the node id's are changed before they are added
        graph->link(source - 1, target - 1, cost);
    }

    std::cout << graph->Dijkstra() << "\n";
    std::cout << graph->FloydWarshall() << "\n";
    std::cout << graph->Johnson() << "\n";
}
