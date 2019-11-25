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

   public:
    GraphDriver();
    ~GraphDriver();

    static void readData(std::istream& input);
};

#endif  // GRAPHDRIVER_HPP_