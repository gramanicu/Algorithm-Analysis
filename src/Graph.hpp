// Copyright 2019 Grama Nicolae
#ifndef HEADERS_GRAPH_HPP_
#define HEADERS_GRAPH_HPP_

#include <algorithm>
#include <iostream>
#include <vector>

#define uint __UINT_FAST32_TYPE__
#define int32 int_fast32_t

/**
 * @brief An abstract class, defining a general graph
 * As there are mainly 2 implementations of a graph (adjency matrix and adjency
 * array), they had to be linked using a more general approach to a graph.
 */

class Graph {
   protected:
    uint _nodeCount;

    Graph();
    Graph(const uint nodeCount);

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
     * @brief Method to print the contents of the graph
     * @return std::ostream&
     */
    virtual void print(std::ostream& output) const = 0;

   public:
    virtual ~Graph();
    /**
     * @brief Makes a unidirectional link from the source to the target node
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    virtual void link(const uint source, const uint target,
                      const int32 cost = 1) = 0;

    /**
     * @brief Makes a bidirectional link between the source and the target node
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    virtual void linkBoth(const uint source, const uint target,
                          const int32 cost = 1) = 0;

    /**
     * @brief Removes the link from the source to the target node
     * @param source Source node ID
     * @param target Target node ID
     */
    virtual void unlink(const uint source, const uint target) = 0;

    /**
     * @brief Removes the links between the nodes
     * This function removes both links, if that is the case
     * @param source Source node ID
     * @param target Target node ID
     */
    virtual void unlinkBoth(const uint source, const uint target) = 0;

    /**
     * @brief The number of nodes in the graph
     * @return int32
     */
    virtual int32 nodesCount() const = 0;

    /**
     * @brief Computes the shortest path cost using Dijkstra's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    virtual int32 Dijkstra(const uint source, const uint target) const = 0;

    /**
     * @brief Computes the shortest path cost using the Floyd-Warshall algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    virtual int32 FloydWarshall(const uint source, const uint target) const = 0;

    /**
     * @brief Computes the shortest path cost using Johnson's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int32)
     */
    virtual int32 Johnson(const uint source, const uint target) const = 0;

    // Operator overload to print the content of the graph
    friend std::ostream& operator<<(std::ostream& output, const Graph& g);
};

inline Graph::Graph() {}
inline Graph::Graph(const uint nodeCount) : _nodeCount(nodeCount) {}
inline std::ostream& operator<<(std::ostream& output, const Graph& g) {
    g.print(output);
    return output;
}
inline Graph::~Graph() {}

inline bool Graph::nodeIDValid(const uint first, const uint second) const {
    if (first < _nodeCount) {
        if (second < _nodeCount) {
            if (first != second) {
                return true;
            }
        }
    }
    return false;
}

#endif  // HEADERS_GRAPH_HPP_
