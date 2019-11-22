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
    /**
     * @brief Method to print the contents of the graph
     * @return std::ostream&
     */
    void print(std::ostream& output) const override;

   private:
    std::vector<std::vector<int32>> adjency;

    /**
     * @brief Check if the specified id's are valid (can check just 1)
     * If two id's are specified, they are valid if they are lower than the
     * number of nodes (quite obvious), and if they are different
     * @param first First node to check
     * @param second Second node to check
     * @return Whether the ID's are valid
     */
    bool nodeIDValid(const uint first, const uint second = 0);

   public:
    /**
     * @brief Construct a new Fast Graph object
     * Builds the adjency matrix and updates the node count
     * @param nodeCount
     */
    FastGraph(const uint nodeCount);
    /**
     * @brief Destroy the Fast Graph object
     */
    ~FastGraph();

    /**
     * @brief Makes a unidirectional link from the source to the target node
     * Cost must be != 0
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    void link(const uint source, const uint target,
              const int cost = 1) override;

    /**
     * @brief Makes a bidirectional link between the source and the target node
     * Cost must be != 0
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    void linkBoth(const uint source, const uint target,
                  const int cost = 1) override;

    /**
     * @brief Removes the link from the source to the target node
     * @param source Source node ID
     * @param target Target node ID
     */
    void unlink(const uint source, const uint target) override;

    /**
     * @brief Removes the links between the nodes
     * This function removes both links, if that is the case
     * @param source Source node ID
     * @param target Target node ID
     */
    void unlinkBoth(const uint source, const uint target) override;

    /**
     * @brief The number of nodes in the graph
     * @return int
     */
    int nodesCount() const override;

    /**
     * @brief Computes the shortest path cost using Dijkstra's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    int Dijkstra(const uint source, const uint target) const override;

    /**
     * @brief Computes the shortest path cost using the Floyd-Warshall algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    int FloydWarshall(const uint source, const uint target) const override;

    /**
     * @brief Computes the shortest path cost using Johnson's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    int Johnson(const uint source, const uint target) const override;
};

#endif  // HEADERS_FASTGRAPH_HPP_