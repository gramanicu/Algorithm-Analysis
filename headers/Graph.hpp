// Copyright 2019 Grama Nicolae
#ifndef HEADERS_GRAPH_HPP_
#define HEADERS_GRAPH_HPP_

#include <iostream>

#define uint __UINT_FAST32_TYPE__

/**
 * @brief An abstract class, defining a general graph
 * As there are mainly 2 implementations of a graph (adjency matrix and adjency
 * array), they had to be linked using a more general approach to a graph.
 */

class Graph {
   protected:
    uint _nodeCount;

    /**
     * @brief Method to print the contents of the graph
     * @return std::ostream&
     */
    virtual void print(std::ostream& output) const;

   public:
    Graph();
    Graph(const int nodeCount);
    ~Graph();

    /**
     * @brief Makes a unidirectional link from the source to the target node
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    virtual void link(const int source, const int target, const int cost = 1);

    /**
     * @brief Makes a bidirectional link between the source and the target node
     * @param source Source node ID
     * @param target Target node ID
     * @param cost The length/cost of the link/edge (optional, default 1)
     */
    virtual void linkBoth(const int source, const int target,
                          const int cost = 1);

    /**
     * @brief Removes the link from the source to the target node
     * @param source Source node ID
     * @param target Target node ID
     */
    virtual void unlink(const int source, const int target);

    /**
     * @brief Removes the links between the nodes
     * This function removes both links, if that is the case
     * @param source Source node ID
     * @param target Target node ID
     */
    virtual void unlinkBoth(const int source, const int target);

    /**
     * @brief The number of nodes in the graph
     * @return int
     */
    virtual int nodesCount() const;

    /**
     * @brief Computes the shortest path cost using Dijkstra's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    virtual int Dijkstra(const int source, const int target) const;

    /**
     * @brief Computes the shortest path cost using the Floyd-Warshall algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    virtual int FloydWarshall(const int source, const int target) const;

    /**
     * @brief Computes the shortest path cost using Johnson's algorithm
     * @param source Source node ID
     * @param target Target node ID
     * @return The cost (int)
     */
    virtual int Johnson(const int source, const int target) const;

    // Operator overload to print the content of the graph
    friend std::ostream& operator<<(std::ostream& output, const Graph& g);
};

inline std::ostream& operator<<(std::ostream& output, const Graph& g) {
    g.print(output);
    return output;
}

#endif  // HEADERS_GRAPH_HPP_
