#include <iostream>
#include "../src/GraphDriver.hpp"

int main() {
    GraphDriver::getInstance();

    GraphDriver::readData(std::cin);

    return 0;
}
