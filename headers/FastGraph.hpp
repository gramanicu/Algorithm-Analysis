// Copyright 2019 Grama Nicolae
#ifndef HEADERS_FASTGRAPH_HPP_
#define HEADERS_FASTGRAPH_HPP_

#include <vector>
#include "Graph.hpp"

#define int32 int_fast32_t

/**
 * @brief A time-optimised graph
 * This is a graph implementation that is speed optimised. To do so, it uses an
 * adjency matrix, which has the advantage of fast access times. The main
 * downside of this specific implementation is that it is very
 * space-ineffiecint, especially for sparse graphs
 */

class FastGraph : Graph {
   protected:
    void print(std::ostream& output) const override;

   private:
    std::vector<std::vector<int32>> adjency;

   public:
    FastGraph(const int nodeCount);
    void link(const int source, const int target, const int cost = 1) override;
    void linkBoth(const int source, const int target, const int cost = 1) override;
    void unlink(const int source, const int target) override;
    void unlinkBoth(const int source, const int target) override;
    int nodesCount() const override;
    int Dijkstra(const int source, const int target) const override;
    int FloydWarshall(const int source, const int target) const override;
    int Johnson(const int source, const int target) const override;
};

#endif  // HEADERS_FASTGRAPH_HPP_