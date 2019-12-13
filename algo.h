#ifndef ALGO_H
#define ALGO_H

#include <stdint.h>
#include <vector>

#define int32 int_fast32_t

typedef std::pair<int, int> edge;

class GlobalVariables {
   public:
    static bool has_negatives;
    static int node_count;
    static int edge_count;
    static std::vector<std::vector<int32>> last_output;
};

/**
 * For a given input graph T, computes the distance from every node to every
 * other node in the graph.
 *
 * @graph: The graph is represented using adjacency lists (graph[i] - gives you
 * the neighbours of node i) *
 * @returns: The adjacency matrix with the minimum distances between every node.
 * If there is no way reach node j from i, store -1 in the matrix. (print it as
 * "inf" in the tests)
 */
std::vector<std::vector<int32>> shortest_path_all(
    const std::vector<std::vector<edge>>& graph);

std::vector<std::vector<int32>> Dijkstra(
    const std::vector<std::vector<edge>>& graph);
std::vector<std::vector<int32>> FloydWarshall(
    const std::vector<std::vector<edge>>& graph);
std::vector<std::vector<int32>> Johnson(
    const std::vector<std::vector<edge>>& graph);

#endif  // Algo_H
