#include "generator.hpp"

std::vector<std::vector<Edge>> Generator::threaded_graph;

int main() {
    Generator g;
    g.setup();
    g.generateTests(100);
    return 0;
}
