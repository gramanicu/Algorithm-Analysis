// Copyright 2019 Grama Nicolae
#include <chrono>
#include <fstream>
#include <sstream>
#include <utility>
#include "../src/GraphDriver.hpp"

#define INPUT_FOLDER "./other_tests/in/"
#define OUTPUT_FOLDER_J "./other_tests/johnson/"
#define OUTPUT_FOLDER_D "./other_tests/dijkstra/"
#define OUTPUT_FOLDER_F "./other_tests/floydwarshall/"
#define TIMINGS_FOLDER "./other_tests/timings/"
#define TEST_COUNT 400

#define duration(a) \
    std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

typedef std::chrono::high_resolution_clock::time_point TimeVar;

template <typename F, typename... Args>
double functionTime(F func, Args&&... args) {
    TimeVar t1 = timeNow();
    func(std::forward<Args>(args)...);
    return duration(timeNow() - t1);
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

int main() {
    std::ofstream timed, timef, timej;

    std::stringstream stimed, stimef, stimej;
    stimed << TIMINGS_FOLDER << "dijkstra.txt";
    stimef << TIMINGS_FOLDER << "floydwarshall.txt";
    stimej << TIMINGS_FOLDER << "johnson.txt";

    timed.open(stimed.str());
    timef.open(stimef.str());
    timej.open(stimej.str());

    for (int i = 0; i < TEST_COUNT; i++) {
        GraphDriver driver;
        std::stringstream filename;
        filename << INPUT_FOLDER << "test" << i << ".in";

        std::ifstream input;
        input.open(filename.str());

        if (input.is_open()) {
            std::cout << filename.str() << "\n";
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

            // Compute running times
            int tcount = 0;
            tcount += functionTime(driver.FloydWarshall);
            timef << driver.lastNodes << " " << driver.lastEdges << " "
                  << (int)tcount << "\n";

            tcount = 0;
            tcount += functionTime(driver.Dijkstra);
            timed << driver.lastNodes << " " << driver.lastEdges << " "
                  << (int)tcount << "\n";

            tcount = 0;
            tcount += functionTime(driver.Johnson);
            timej << driver.lastNodes << " " << driver.lastEdges << " "
                  << (int)tcount << "\n";
        }
    }

    return 0;
}
