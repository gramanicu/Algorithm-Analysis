// Copyright 2019 Grama Nicolae
#include "../headers/FastGraph.hpp"

/**
 * @brief Construct a new Fast Graph object
 * Builds the adjency matrix and updates the node count
 * @param nodeCount
 */
FastGraph::FastGraph(const uint nodeCount) : Graph(nodeCount) {
    adjency = std::vector<std::vector<int32>>(nodeCount,
                                              std::vector<int32>(nodeCount, 0));
}

/**
 * @brief Destroy the Fast Graph object
 */
FastGraph::~FastGraph() {}

/**
 * @brief Check if the specified id's are valid (can check just 1)
 * If two id's are specified, they are valid if they are lower than the number
 * of nodes (quite obvious), and if they are different
 * @param first First node to check
 * @param second Second node to check
 * @return Whether the ID's are valid
 */
bool FastGraph::nodeIDValid(const uint first, const uint second) {
    if (first < _nodeCount) {
        if (second < _nodeCount) {
            if (first != second) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Makes a unidirectional link from the source to the target node
 * Cost must be != 0
 * @param source Source node ID
 * @param target Target node ID
 * @param cost The length/cost of the link/edge (optional, default 1)
 */
void FastGraph::link(const uint source, const uint target, const int cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    adjency[source][target] = cost;
}

/**
 * @brief Makes a bidirectional link between the source and the target node
 * Cost must be != 0
 * @param source Source node ID
 * @param target Target node ID
 * @param cost The length/cost of the link/edge (optional, default 1)
 */
void FastGraph::linkBoth(const uint source, const uint target, const int cost) {
    if (!nodeIDValid(source, target)) return;
    if (!cost) return;
    adjency[source][target] = cost;
    adjency[target][source] = cost;
}

/**
 * @brief Removes the link from the source to the target node
 * @param source Source node ID
 * @param target Target node ID
 */
void FastGraph::unlink(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;
    adjency[source][target] = 0;
}

/**
 * @brief Removes the links between the nodes
 * This function removes both links, if that is the case
 * @param source Source node ID
 * @param target Target node ID
 */
void FastGraph::unlinkBoth(const uint source, const uint target) {
    if (!nodeIDValid(source, target)) return;
    adjency[source][target] = 0;
    adjency[target][source] = 0;
}

/**
 * @brief The number of nodes in the graph
 * @return int
 */
int FastGraph::nodesCount() const { return _nodeCount; }

/**
 * @brief Computes the shortest path cost using Dijkstra's algorithm
 * @param source Source node ID
 * @param target Target node ID
 * @return The cost (int)
 */
int FastGraph::Dijkstra(const uint source, const uint target) const {
    return 0;
}

/**
 * @brief Computes the shortest path cost using the Floyd-Warshall algorithm
 * @param source Source node ID
 * @param target Target node ID
 * @return The cost (int)
 */
int FastGraph::FloydWarshall(const uint source, const uint target) const {
    return 0;
}

/**
 * @brief Computes the shortest path cost using Johnson's algorithm
 * @param source Source node ID
 * @param target Target node ID
 * @return The cost (int)
 */
int FastGraph::Johnson(const uint source, const uint target) const { return 0; }

/**
 * @brief Method to print the contents of the graph
 * @return std::ostream&
 */
void FastGraph::print(std::ostream &output) const {
    for (auto &row : adjency) {
        for (auto &elem : row) {
            output << elem << " ";
        }
        output << "\n";
    }
}