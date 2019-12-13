#include "Generator.hpp"

std::vector<std::vector<Edge>> Generator::threaded_graph;

int main() {
    Generator g;
    g.generateTests(NUM_OF_TESTS);
    return 0;
}
