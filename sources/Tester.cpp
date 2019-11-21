#include <iostream>
#include "../headers/FastGraph.hpp"

int main() {
    FastGraph g(10);
    g.link(0, 1, 2);
    g.link(0, 2, 78);
    g.link(0, 3, 5);
    g.link(0, 4, 13);
    g.link(0, 5, 23);
    g.link(0, 6, 6);
    g.link(0, 7, 1);
    g.linkBoth(9, 8, 100);
    std::cout << g;
    return 0;
}
