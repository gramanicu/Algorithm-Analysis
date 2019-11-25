#include "Generator.hpp"

int main() {
    std::ifstream input;
    input.open("generate.in");
    Generator::generate(input);

    return 0;
}