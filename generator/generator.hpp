#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

class Edge {
   public:
    int source;
    int destination;
    int distance;

    Edge();
    Edge(int source, int destination, int distance)
        : source(source), destination(destination), distance(distance){};
};

#define MAX_NODE_COUNT 10000
#define MAX_EDGE_COUNT 100000
#define INPUTS_FOLDER "../in/"

class Generator {
   private:
    int thread_count;
    static std::vector<std::vector<Edge>> threaded_graph;
    int current_test;

    /*
        As this function will be run on multiple threads, we want to
        generate only a part of the graph. So, we need to specify
        the starting node, nodes count and edges count
    */
    static void generateGraph(int nodeI, int nodes_count, int edges_count,
                              int total_nodes, const int threadI) {
        int cNode = nodeI;
        std::vector<Edge> graph;

        while (cNode != nodeI + nodes_count && edges_count != 0) {
            int current_dest = 0;

            while (current_dest != total_nodes) {
                if (current_dest != cNode) {
                    graph.push_back(Edge(cNode, current_dest, 1));
                }
                current_dest++;
            }

            cNode++;
        }

        threaded_graph[threadI] = graph;
    }

   public:
    Generator() { current_test = 0; }

    void setup() {
        thread_count = std::thread::hardware_concurrency();
    }

    void generateTests(int num_of_tests) {
        std::ofstream output;
        int nodeRate = MAX_NODE_COUNT / num_of_tests;
        int current_nodes = nodeRate;

        // For each test
        while (current_test != num_of_tests) {
            int test_nodes = current_nodes;
            int thread_node_count = current_nodes / thread_count;
            int thread_node_index = 0;
            int thread_edge_count = std::min(MAX_EDGE_COUNT, test_nodes);
            thread_edge_count /= thread_count;
            std::vector<std::thread> threads;
            threaded_graph = std::vector<std::vector<Edge>>(thread_count);

            for (int i = 0; i < thread_count; ++i) {
                threads.push_back(std::thread(
                    generateGraph, thread_node_index, thread_node_count,
                    thread_edge_count, test_nodes, i));
                thread_node_index += thread_node_count;
            }

            for (auto& thread : threads) {
                thread.join();
            }

            for (int i = 0; i < thread_count; ++i) {
                std::cout << threaded_graph[i].size() << "\n";
            }

            current_test++;
            std::cout << "test " << current_test << "\n";
        }
    }

    // std::stringstream filename;
    // filename << INPUTS_FOLDER << "test" << std::to_string(current_test)
    //          << ".in";
    // output.open(filename.str());
    // output << Generator::last_nodes << " " << Generator::last_edges
    //        << "\n";
    // output << Generator::last_test;
};

#endif  // GENERATOR_HPP_