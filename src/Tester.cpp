#include "../src/GraphDriver.hpp"

#define INPUT_FOLDER "./in/"
#define OUTPUT_FOLDER_J "./out/johnson/"
#define OUTPUT_FOLDER_D "./out/dijkstra/"
#define OUTPUT_FOLDER_F "./out/floydwarshall/"
#define TEST_COUNT 800

#include <fstream>
#include <sstream>

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

int main() {
    for (int i = 0; i < TEST_COUNT; i++) {
        GraphDriver driver;
        std::stringstream filename;
        filename << INPUT_FOLDER << "test" << i << ".in";

        std::cout << filename.str() << "\n";

        std::ifstream input;
        input.open(filename.str());

        if (input.is_open()) {
            driver.readData(input);

            input.close();
            input.clear();

            filename.str(std::string(""));

            // Johnson output
            filename << OUTPUT_FOLDER_J << "test" << i << ".out";

            std::ofstream output;
            output.open(filename.str());
            output << driver.Johnson();

            output.close();
            output.clear();

            filename.str(std::string(""));

            // Dijkstra output
            filename << OUTPUT_FOLDER_D << "test" << i << ".out";

            output.open(filename.str());
            output << driver.Dijkstra();

            output.close();
            output.clear();

            filename.str(std::string(""));

            // Floyd-Warshall output
            filename << OUTPUT_FOLDER_F << "test" << i << ".out";

            output.open(filename.str());
            output << driver.FloydWarshall();

            output.close();
            output.clear();
        }
    }

    return 0;
}
