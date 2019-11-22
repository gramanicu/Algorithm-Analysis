// Copyright 2019 Grama Nicolae
#include "GraphDriver.hpp"

#define DENSITY_THRESHOLD 1.5f

GraphDriver::GraphDriver() {}
GraphDriver::GraphDriver(const GraphDriver& other) {}
GraphDriver* GraphDriver::instance = nullptr;
Graph* GraphDriver::graph = nullptr;

GraphDriver::~GraphDriver() { 
    delete graph;
    delete instance; 
}

GraphDriver* GraphDriver::getInstance() {
    if (instance == nullptr) {
        instance = new GraphDriver();
    }
    return instance;
}

void GraphDriver::readData(std::istream& input) {
    uint nodeCount, edgeCount = 0;
    std::string ignoredData;

    std::getline(input, ignoredData);
    while (std::getline(input, ignoredData)) {
        edgeCount++;
    }

    input.clear();
    input.seekg(0, input.beg);

    input >> nodeCount;

    std::cout << "Vertices : " << nodeCount << "\n";
    std::cout << "Edges : " << edgeCount << "\n";

    double graphDensity;

    graphDensity = 2.0 * double(edgeCount) /
                   (double(nodeCount) * (double(nodeCount) - 1.0f));
    std::cout << "Graph density " << graphDensity << "\n";

    if (graphDensity < DENSITY_THRESHOLD) {
        graph = new SmallGraph(nodeCount);
        std::cout << "Sparse Graph\n";
    } else {
        graph = new FastGraph(nodeCount);
        std::cout << "Dense Graph\n";
    }

    while (!input.eof()) {
        uint source, target;
        int32 cost;

        input >> source >> target >> cost;

        graph->link(source, target, cost);
    }

    std::cout << *graph << '\n';
}