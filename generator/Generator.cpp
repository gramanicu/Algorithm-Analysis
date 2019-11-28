// Copyright 2019 Grama Nicolae
#include "Generator.hpp"
#include <iostream>

std::vector<Edge> Generator::last_test;
uint Generator::last_nodes;
uint Generator::last_edges;
bool Generator::has_negative_cycles;
std::vector<std::vector<int32>> Generator::last_solution;

std::ostream& operator<<(std::ostream& output, const std::vector<Edge> vector) {
    for (auto& elem : vector) {
        output << elem;
    }
    output << "\n";
    return output;
}

std::ostream& operator<<(std::ostream& output,
                         const std::vector<std::vector<int32>> matrix) {
    for (auto& row : matrix) {
        for (auto& elem : row) {
            if (elem == INT32_MAX) {
                output << "inf ";
            } else {
                output << elem << " ";
            }
        }
        output << "\n";
    }
    return output;
}

bool Generator::is_duplicate(const uint source, const uint target,
                             const std::vector<Edge> links) {
    if (source == target) {
        return true;
    }

    for (auto& edge : links) {
        if (edge.getSource() == source) {
            if (edge.getTarget() == target) {
                return true;
            }
        }
    }

    return false;
}

std::vector<Edge> Generator::build_test(const uint nodes, uint edges,
                                        const bool has_negative,
                                        const bool only_unit,
                                        const bool fully_random,
                                        const bool negative_cycles) {
    using namespace EasyRand;

    if (edges > nodes * (nodes - 1) / 2) {
        edges = nodes * (nodes - 1) / 2;
    }

    int32 min_cost, max_cost;

    // Apply the "settings"
    if (only_unit) {
        if (has_negative) {
            min_cost = -1;
        } else {
            min_cost = 1;
        }
        max_cost = 1;
    } else {
        if (fully_random) {
            if (has_negative) {
                min_cost = INT32_MIN;
            } else {
                min_cost = 1;
            }
            max_cost = INT32_MAX - 1;
        } else {
            int max = (nodes > edges) ? nodes : edges;
            if (has_negative) {
                min_cost = -max;
            } else {
                min_cost = 1;
            }
            max_cost = max;
        }
    }

    int tries = 0;
    // Will build graphs untill no negative cycles are detected (if the option is active)
    do {
        std::vector<Edge> links;

        double current_step = 0.0f;
        double step = double(nodes) / double(edges);
        uint remaining = edges;

        // If we have more edges than nodes, we can give an edge to each node
        while (step < 1) {
            for (uint index = 0; index < nodes; ++index) {
                // Generate a link that doesn't exist already
                uint target;
                do {
                    target = Random::randInt(0, nodes - 1);
                } while (is_duplicate(index, target, links));

                // Make sure there isn't a link with 0 cost
                int32 cost;
                do {
                    cost = Random::randInt(min_cost, max_cost);
                } while (cost == 0);

                // Add the link to the list
                links.push_back(Edge(index, target, cost));
            }
            remaining -= nodes;
            step = double(nodes) / remaining;
        }

        // Distribute the remaining edges
        while (remaining) {
            uint source = current_step;

            // Generate a link that doesn't exist already
            uint target;
            do {
                target = Random::randInt(0, nodes - 1);
            } while (is_duplicate(source, target, links));

            // Make sure there isn't a link with 0 cost
            int32 cost;
            do {
                cost = Random::randInt(min_cost, max_cost);
            } while (cost == 0);

            links.push_back(Edge(source, target, cost));
            current_step += step;
            remaining--;
        }

        // Sort the links (to look good)
        std::sort(links.begin(), links.end(), [](const Edge& a, const Edge& b) {
            return a.getSource() < b.getSource();
        });

        last_test = std::move(links);
        last_nodes = nodes;
        last_edges = edges;
        tries++;
        
        has_negative_cycles = build_reference();
    } while (has_negative_cycles && !negative_cycles && tries < MAX_CYCLE_TRIES);

    return last_test;
}

bool Generator::build_reference() {
    // Use Floyd-Warshall Algorithm
    std::vector<std::vector<int32>> distances = std::vector<std::vector<int32>>(
        last_nodes, std::vector<int32>(last_nodes, INT32_MAX));

    // Create the initial matrix (adjency matrix)
    for (uint i = 0; i < last_nodes; ++i) {
        distances[i][i] = 0;
    }

    for (auto& edge : last_test) {
        distances[edge.getSource()][edge.getTarget()] = edge.getCost();
    }

    for (uint inter = 0; inter < last_nodes; ++inter) {
        for (uint source = 0; source < last_nodes; ++source) {
            for (uint target = 0; target < last_nodes; ++target) {
                int32 newDistance =
                    distances[source][inter] + distances[inter][target];

                // Keep the sum infinite, if that is the case
                if (distances[source][inter] == INT32_MAX ||
                    distances[inter][target] == INT32_MAX) {
                    newDistance = INT32_MAX;
                }

                if (newDistance < distances[source][target]) {
                    distances[source][target] = newDistance;
                }
            }
        }
    }

    last_solution = distances;

    for (uint i = 0; i < last_nodes; i++) {
        if (distances[i][i] < 0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Will generate the tests specified in the input
 * The test will have an increasing number of nodes, from MAX_NODES/test_count
 * to the maximum number of nodes. The graphs have a randomised density, with
 * the number of edges ranging from nodes/2 to maximum number of edges.
 * When there are no negative cycles, MAX_NODES_POSITIVE is used instead
 * of MAX_NODES, as the graphs can be solved faster (and removes the chance
 * to generate negative cycles)
 * @param input 
 */
void Generator::generate(std::istream& input) {
    // Read the number of test types
    std::ofstream output;
    uint types;
    uint testCount = 0;
    input >> types;

    for (uint i = 0; i < types; i++) {
        uint num_test, nodes, edges;
        bool negatives, unity, random, ncycles;

        input >> num_test >> negatives >> unity >> random >> ncycles;

        
        // Try to get an even distribution of node counts for the tests
        int increase_nodes_by;
        if(negatives) {
            increase_nodes_by = MAX_NODES / num_test;
        } else {
            increase_nodes_by = MAX_NODES_POSITIVE / num_test;
        }
        nodes = increase_nodes_by;

        std::ofstream nlogs, plogs;
        nlogs.open("negative.txt");
        plogs.open("positive.txt");

        while (num_test != 0) {
            // Randomise the number of edges
            edges =
                EasyRand::Random::randInt(nodes / 2, nodes * (nodes - 1) / 2);

            // Build the test
            Generator::build_test(nodes, edges, negatives, unity, random,
                                  ncycles);

            // Move generated data to input folder
            std::stringstream filename;
            filename << INPUTS_FOLDER << "test" << std::to_string(testCount)
                     << ".in";
            output.open(filename.str());
            std::cout << filename.str() << "\n";

            output << Generator::last_nodes << " " << Generator::last_edges
                   << "\n";
            output << Generator::last_test;
            // std::cout << Generator::last_nodes << " " <<
            // Generator::last_edges << "\n"; std::cout << Generator::last_test;

            output.close();
            output.clear();
            filename.str(std::string(""));

            // Move generated to to reference folder
            filename << REFERENCE_FOLDER << "test" << std::to_string(testCount)
                     << ".ref";
            output.open(filename.str());
            std::cout << filename.str() << "\n";
            output << last_solution;

            output.close();
            output.clear();
            filename.str(std::string(""));

            // If the test shouldn't have negative cycles, but a graph without them
            // couldn't be generated, log that to a file
            if(has_negative_cycles && !ncycles) {
                nlogs << "Test " << testCount << " has negative cycles\n";
            } else if(!has_negative_cycles && !ncycles) {
                plogs << "Test " << testCount << " doesn't have negative cycles\n";
            }

            num_test--;
            testCount++;
            nodes += increase_nodes_by;
        }

        nlogs.close();
        nlogs.clear();
        plogs.close();
        plogs.clear();
    }
}