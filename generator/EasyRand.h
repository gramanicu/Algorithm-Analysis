// Copyright Grama Nicolae 2019
#ifndef HEADERS_EASYRAND_H_
#define HEADERS_EASYRAND_H_

#include <stdint.h>
#include <random>

namespace EasyRand {
class Random {
   private:
    static bool initialised;
    static std::mt19937 generator;
    static std::uniform_int_distribution<int32_t> booldistribution;
    static std::uniform_int_distribution<int32_t> distribution;
    static std::uniform_real_distribution<double> realdistribution;

    static void seed();
    static bool checkInterval(const int32_t iStart, const int32_t iEnd);
    static bool checkInterval(const double iStart, const double iEnd);

    Random() = delete;

   public:
    static bool randBool();
    static int32_t randInt();
    static int32_t randInt(const int32_t iStart, const int32_t iEnd);
    static double randReal();
    static double randReal(const double iStart, const double iEnd);
};
}  // namespace EasyRand

#endif  // HEADERS_EASYRAND_H_