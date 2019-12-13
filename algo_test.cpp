#include "algo.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "./generator/Generator.hpp"

#define OUT_FOLDER "./out/test"
#define TIMES_FILE "./other_tests/time.csv"
#define PRINT_RESULT false

// Time-counting related (code found on github :) )
#define duration(a) \
    std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

typedef std::chrono::high_resolution_clock::time_point TimeVar;

template <typename F, typename... Args>
double functionTime(F func, Args&&... args) {
    TimeVar t1 = timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow() - t1);
}

std::ostream& operator<<(std::ostream& output,
                         const std::vector<std::vector<int32>> matrix) {
    for (auto& row : matrix) {
        for (auto& elem : row) {
            if (elem == -1 || elem == INT32_MAX) {
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
    std::stringstream timesname;
    timesname << TIMES_FILE;
    std::ofstream times;
    times.open(timesname.str());
    times << "times,nodes\n";

    for (int i = 0; i < NUM_OF_TESTS; i++) {
        std::stringstream filename;
        filename << "./in/test" << i << ".in";

        std::ifstream input;
        input.open(filename.str());

        std::vector<std::vector<edge>> edges;

        if (input.is_open()) {
            std::cout << filename.str() << "\n";
            int nodeCount, edgeCount;

            input >> nodeCount >> edgeCount;
            GlobalVariables::node_count = nodeCount;
            GlobalVariables::edge_count = edgeCount;

            edge empty = std::make_pair(0, 0);
            edges = std::vector<std::vector<edge>>(nodeCount,
                                                   std::vector<edge>(0, empty));

            for (int i = 0; i < edgeCount; i++) {
                int source, target, cost;
                input >> source >> target >> cost;
                if (cost < 0) {
                    GlobalVariables::has_negatives = true;
                }
                edges[source - 1].push_back(std::make_pair(target - 1, cost));
            }

            std::stringstream outputname;
            outputname << OUT_FOLDER << i << ".out";
            std::ofstream output;
            output.open(outputname.str());

            // Print times
            int tcount = 0;
            tcount += functionTime(shortest_path_all, edges);
            times << (int)tcount << "," << GlobalVariables::node_count << "\n";

            if (PRINT_RESULT) {
                output << GlobalVariables::last_output;
            }
            input.close();
            output.close();
        }
    }
    times.close();
}