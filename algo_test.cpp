// Copyright Grama Nicolae 2019
#include "algo.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "./generator/Generator.hpp"

#define OUT_FOLDER "./out/test"
#define TIMES_FILE "./other_tests/btime.csv"
#define DTIMES_FILE "./other_tests/dtime.csv"
#define FTIMES_FILE "./other_tests/ftime.csv"
#define JTIMES_FILE "./other_tests/jtime.csv"
#define PRINT_RESULT true

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
    std::stringstream times_name;
    times_name << TIMES_FILE;
    std::ofstream best_times, dtimes, ftimes, jtimes;

    // Prepare the output for the "stopwatch"
    best_times.open(times_name.str());
    times_name.str(std::string(""));
    times_name << DTIMES_FILE;
    dtimes.open(times_name.str());
    times_name.str(std::string(""));
    times_name << FTIMES_FILE;
    ftimes.open(times_name.str());
    times_name.str(std::string(""));
    times_name << JTIMES_FILE;
    jtimes.open(times_name.str());
    times_name.str(std::string(""));

    best_times << "times,nodes\n";
    dtimes << "times,nodes\n";
    ftimes << "times,nodes\n";
    jtimes << "times,nodes\n";

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

            // Print times (average of 3 runs), for the best algorithm
            int tcount = 0;
            tcount += functionTime(shortest_path_all, edges);
            tcount += functionTime(shortest_path_all, edges);
            tcount += functionTime(shortest_path_all, edges);
            tcount /= 3;
            best_times << (int)tcount << "," << GlobalVariables::node_count << "\n";

            // Print the result using the best method
            if (PRINT_RESULT) {
                output << GlobalVariables::last_output;
            }

            tcount = 0;
            tcount += functionTime(Dijkstra, edges);
            tcount += functionTime(Dijkstra, edges);
            tcount += functionTime(Dijkstra, edges);
            tcount /= 3;
            dtimes << (int)tcount << "," << GlobalVariables::node_count << "\n";

            tcount = 0;
            tcount += functionTime(FloydWarshall, edges);
            tcount += functionTime(FloydWarshall, edges);
            tcount += functionTime(FloydWarshall, edges);
            tcount /= 3;
            ftimes << (int)tcount << "," << GlobalVariables::node_count << "\n";
            
            tcount = 0;
            tcount += functionTime(Johnson, edges);
            tcount += functionTime(Johnson, edges);
            tcount += functionTime(Johnson, edges);
            tcount /= 3;
            jtimes << (int)tcount << "," << GlobalVariables::node_count << "\n";

            input.close();
            output.close();
        }
    }
    best_times.close();
    dtimes.close();
    ftimes.close();
    jtimes.close();
}