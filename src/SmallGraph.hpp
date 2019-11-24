// Copyright 2019 Grama Nicolae
#ifndef HEADERS_SMALLGRAPH_HPP_
#define HEADERS_SMALLGRAPH_HPP_

#include <vector>
#include "Graph.hpp"

/**
 * @brief A space-optimised graph
 *
 */

class SmallGraph : public Graph {
   protected:
    void print(std::ostream& output) const override;

   private:
    std::vector<std::vector<std::pair<uint, int32>>> adjency;
    uint _nodeCount;

    /**
     * @brief Check if the specified id's are valid (can check just 1)
     * If two id's are specified, they are valid if they are lower than the
     * number of nodes (quite obvious), and if they are different
     * @param first First node to check
     * @param second Second node to check
     * @return Whether the ID's are valid
     */
    bool nodeIDValid(const uint first, const uint second = 0) const;
    
    /**
     * @brief Returns the neighbouring nodes of the source node
     * Only the nodes that can be reached starting from the source node
     * @param source The starting node
     * @return std::vector<uint> The list of neighbours
     */
    std::vector<std::pair<uint, int32>> neighbours(const uint source) const;

    bool edgeExist(const uint source, const uint target) const;

   public:
    /**
     * @brief Construct a new Small Graph object
     * Builds the adjency matrix and updates the node count
     * @param nodeCount
     */
    SmallGraph(const uint nodeCount);
    /**
     * @brief Destroy the Small Graph object
     */
    ~SmallGraph();

    /**
     * @brief Makes a unidirectional link from the source to the target node
     * Cost must be != 0
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    void link(const uint source, const uint target,
              const int32 cost = 1) override;

    /**
     * @brief Makes a bidirectional link between the source and the target node
     * Cost must be != 0
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    void linkBoth(const uint source, const uint target,
                  const int32 cost = 1) override;

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
     * @return int32
     */
    int32 nodesCount() const override;

    /**
     * @brief Computes the shortest path cost using Dijkstra's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    int32 Dijkstra(const uint source, const uint target) const override;

    /**
     * @brief Computes the shortest path cost using the Floyd-Warshall algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    int32 FloydWarshall(const uint source, const uint target) const override;

    /**
     * @brief Computes the shortest path cost using Johnson's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    int32 Johnson(const uint source, const uint target) const override;
};

#endif  // HEADERS_SMALLGRAPH_HPP_