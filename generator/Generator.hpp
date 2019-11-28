// Copyright 2019 Grama Nicolae
#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "EasyRand.h"

#define INPUTS_FOLDER "../in/"
#define REFERENCE_FOLDER "../ref/"
#define uint __UINT_FAST32_TYPE__
#define int32 int_fast32_t
#define MAX_NODES 250
#define MAX_NODES_POSITIVE 500
#define MAX_CYCLE_TRIES 50


class Edge {
   private:
    uint _source;
    uint _target;
    int32 _cost;

   public:
    Edge() : _source(0), _target(0), _cost(0){};
    Edge(const uint source, const uint target, const int32 cost)
        : _source(source), _target(target), _cost(cost){};

    uint getSource() const { return _source; }
    uint getTarget() const { return _target; }
    int32 getCost() const { return _cost; }

    // Source and target +1 to respect the "external" node names
    friend std::ostream& operator<<(std::ostream& output, const Edge& e) {
        output << e._source + 1 << " " << e._target + 1 << " " << e._cost
               << "\n";
        return output;
    }
};

class Generator {
   private:
    Generator() = delete;

    static std::vector<Edge> last_test;
    static std::vector<std::vector<int32>> last_solution;

    static bool is_duplicate(const uint source, const uint target,
                             const std::vector<Edge> links);
    static uint last_nodes;
    static uint last_edges;
    static bool has_negative_cycles;

    /**
     * @brief Generates a graph that will be tested
     * @param nodes The number of nodes/vertices of the graph
     * @param edges The number of edges of the graph
     * @param has_negative Whether the graph has negative costs
     * @param only_unit Whether the graph has only costs = 1
     * @param fully_random Whether the graph has purely random costs
     * @param negative_cycles Whether or not the graph will have
     * negative cycles (note - it isn't guaranteed possible)
     * @return std::vector<Edge> A vector with the edges of the graph
     */
    static std::vector<Edge> build_test(const uint nodes, uint edges,
                                        const bool has_negative,
                                        const bool only_unit,
                                        const bool fully_random,
                                        const bool negative_cycles);

    /**
     * @brief Builds the reference (solution)
     * Will return if the graph contains negative cycles
     * @return true Has negative cycles
     * @return false Doesn't have negative cycles
     */
    static bool build_reference();

   public:
    static void generate(std::istream& input);
};

#endif  // GENERATOR_HPP_