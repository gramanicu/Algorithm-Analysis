// Copyright 2019 Grama Nicolae
#ifndef GRAPHDRIVER_HPP_
#define GRAPHDRIVER_HPP_

#include <iostream>
#include <string>
#include "FastGraph.hpp"
#include "Graph.hpp"
#include "SmallGraph.hpp"

/**
 * @brief A driver program for the graphs
 * This driver, built with singleton pattern (to assure the existance of just 1
 * instance), is used mainly to load data and choose the best graph type for it
 */
class GraphDriver {
   private:
    // Disabling constructor, copy and assignment
    static Graph* graph;
    static bool hasNegatives;

   public:
    GraphDriver();
    ~GraphDriver();

    static void readData(std::istream& input);
    static std::vector<std::vector<int32>> Dijkstra();
    static std::vector<std::vector<int32>> FloydWarshall();
    static std::vector<std::vector<int32>> Johnson();
    static std::vector<std::vector<int32>> Best();
};

#endif  // GRAPHDRIVER_HPP_