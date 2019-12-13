#include "algo.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define TEST_COUNT 10

std::ostream& operator<<(std::ostream& output,
                         const std::vector<std::vector<int32>> matrix) {
    for (auto& row : matrix) {
        for (auto& elem : row) {
            if (elem == -1) {
                output << "inf ";
            } else {
                output << elem << " ";
            }
        }
        output << "\n";
    }
    return output;
}

int main() {
    for (int i = 0; i < TEST_COUNT; i++) {
        std::stringstream filename;
        filename << "./in/test" << i << ".in";

        std::ifstream input;
        input.open(filename.str());

        std::vector<std::vector<edge>> edges;

        if (input.is_open()) {
            // std::cout << filename.str() << "\n";
            int nodeCount, edgeCount;

            input >> nodeCount >> edgeCount;
            node_count = nodeCount;
            edge_count = edgeCount;

            edge empty = std::make_pair(0, 0);
            edges = std::vector<std::vector<edge>>(nodeCount,
                                                   std::vector<edge>(0, empty));

            for (int i = 0; i < edgeCount; i++) {
                int source, target, cost;
                input >> source >> target >> cost;
                edges[source - 1].push_back(std::make_pair(target - 1, cost));
            }
        }

        std::stringstream outputname;
        outputname << "./out/test" << i << ".out";
        std::ofstream output;
        output.open(outputname.str());

        output << shortest_path_all(edges);

        input.close();
        output.close();
    }
}