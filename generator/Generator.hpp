// Copyright Grama Nicolae 2019
#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include "EasyRand.h"

#define MIN_DISTANCE 1
#define MAX_DISTANCE 1
#define NUM_OF_TESTS 50
#define MAX_NODE_COUNT 10000
#define MAX_EDGE_COUNT 100000
#define INPUTS_FOLDER "../in/"

class Edge {
   public:
    int source;
    int destination;
    int distance;

    Edge();
    Edge(int source, int destination, int distance)
        : source(source), destination(destination), distance(distance){};

    friend std::ostream& operator<<(std::ostream& output, const Edge edge) {
        output << edge.source + 1 << " " << edge.destination + 1 << " " << edge.distance;
    return output;
    }

        
};

class Generator {
   private:
    int thread_count;
    static std::vector<std::vector<Edge>> threaded_graph;
    int current_test;

    /*
        As this function will be run on multiple threads, we want to
        generate only a part of the graph. So, we need to specify
        the starting node, starting edge and edges count
    */
    static void generateGraph(int nodeI, int edgeI, int edges_count,
                              int total_nodes, const int threadI) {
        int cNode = nodeI;
        std::vector<Edge> graph;
        int current_dest = edgeI;

        while (edges_count > 0) {
            while (current_dest != total_nodes) {
                if (current_dest != cNode) {
                    int distance = EasyRand::Random::randInt(MIN_DISTANCE, MAX_DISTANCE);
                    graph.push_back(Edge(cNode, current_dest, distance));
                    edges_count--;
                }
                current_dest++;
            }
            cNode++;
            current_dest = 0;
        }
        threaded_graph[threadI] = graph;
    }

   public:
    Generator() { 
        current_test = 0; 
        thread_count = std::thread::hardware_concurrency();
        if (thread_count <= 0) {
            thread_count = 1;
        }
    }

    void generateTests(int num_of_tests) {
        std::ofstream output;
        int nodeRate = MAX_NODE_COUNT / num_of_tests;
        int current_nodes = nodeRate;

        // For each test
        while (current_test != num_of_tests) {
            int test_nodes = current_nodes;
            int thread_node_index = 0;
            int test_edge = std::min(MAX_EDGE_COUNT, int(std::pow(test_nodes, 2)));
            int thread_edge_count = test_edge/thread_count;
            int thread_edge_index = 0;

            std::vector<std::thread> threads;
            threaded_graph = std::vector<std::vector<Edge>>(thread_count);

            for (int i = 0; i < thread_count; ++i) {
                if (i == thread_count - 1) {
                    thread_edge_count += test_edge % thread_count;
                }
                threads.push_back(std::thread(
                    generateGraph, thread_node_index, thread_edge_index,
                    thread_edge_count, test_nodes, i));
                int total_nodes = thread_edge_count/test_nodes;
                thread_edge_index = thread_edge_count % test_nodes;

                thread_node_index += total_nodes;
            }

            for (auto& thread : threads) {
                thread.join();
            }

            std::stringstream filename;
            filename << INPUTS_FOLDER << "test" << std::to_string(current_test)
                     << ".in";
            output.open(filename.str());
            output << test_nodes << " " << test_edge
                   << "\n";
            
            int out_edges = 0;
            for (int i = 0; i < thread_count; ++i) {
                for (auto& edge : threaded_graph[i]) {
                    if(out_edges != test_edge) {
                        output << edge << "\n";
                        out_edges++;
                    }
                }
            }

            output.close();
            output.clear();
            filename.str(std::string(""));

            current_test++;
            current_nodes += nodeRate;
            std::cout << "test " << current_test << "\n";
        }
    }
};

#endif  // GENERATOR_HPP_