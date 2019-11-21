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
 * space-ineffiecint, especially for sparse graphs. For example, for a 10000
 * nodes graph, around 800 MB of RAM will be utilised
 */

class FastGraph : public Graph {
   protected:
    void print(std::ostream& output) const override;

   private:
    std::vector<std::vector<int32>> adjency;
    bool checkNodesID(const uint first, const uint second = 0);

   public:
    FastGraph(const uint nodeCount);
    ~FastGraph();
    void link(const uint source, const uint target,
              const int cost = 1) override;
    void linkBoth(const uint source, const uint target,
                  const int cost = 1) override;
    void unlink(const uint source, const uint target) override;
    void unlinkBoth(const uint source, const uint target) override;
    int nodesCount() const override;
    int Dijkstra(const uint source, const uint target) const override;
    int FloydWarshall(const uint source, const uint target) const override;
    int Johnson(const uint source, const uint target) const override;
};

#endif  // HEADERS_FASTGRAPH_HPP_