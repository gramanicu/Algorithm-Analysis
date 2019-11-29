#include "algo.h"
#include "./src/GraphDriver.hpp"

std::vector<std::vector<int32>> shortest_path_all(const std::vector<std::vector<edge>>& graph) {
    GraphDriver driver;
    driver.setData(graph);
    return driver.Best();
}

