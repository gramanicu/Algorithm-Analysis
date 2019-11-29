#include "algo.h"
#include "./src/GraphDriver.hpp"

std::vector<std::vector<int32>> shortest_path_all(const std::vector<std::vector<edge>>& graph) {
    GraphDriver driver;
    driver.setData(graph);

    std::vector<std::vector<int32>> adj = driver.Best();

    for(auto& row : adj) {
        for(auto& elem : row) {
            if (elem == INT32_MAX)  {
                elem = -1;
            }
        }
    }

    return adj;
}

