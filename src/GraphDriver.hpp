// Copyright 2019 Grama Nicolae
#ifndef HEADERS_GRAPHDRIVER_HPP_
#define HEADERS_GRAPHDRIVER_HPP_

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
    GraphDriver();
    GraphDriver(const GraphDriver& other);
    GraphDriver& operator=(const GraphDriver& other);
    static GraphDriver* instance;
    static Graph* graph;

   public:
    ~GraphDriver();

    static GraphDriver* getInstance();
    static void readData(std::istream& input);
};

#endif  // HEADERS_GRAPHDRIVER_HPP_