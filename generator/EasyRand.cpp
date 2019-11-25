#include "EasyRand.h"
#include <float.h>

using namespace EasyRand;

bool Random::initialised = false;
std::mt19937 Random::generator;
std::uniform_int_distribution<int32_t> Random::booldistribution;
std::uniform_int_distribution<int32_t> Random::distribution;
std::uniform_real_distribution<double> Random::realdistribution;

// Seeds the PRNG
void Random::seed() {
    std::random_device rDevice;
    generator = std::mt19937(rDevice());
    initialised = true;
}

// Check if the interval of integers is valid
bool Random::checkInterval(const int32_t iStart, const int32_t iEnd) {
    if (iStart < iEnd) {
        return true;
    }
    return false;
}

// Check if the interval of real numbers is valid
bool Random::checkInterval(const double iStart, const double iEnd) {
    if (iStart < iEnd) {
        return true;
    }
    return false;
}

// Returns a randomly generated boolean value
bool Random::randBool() {
    booldistribution = std::uniform_int_distribution<int32_t>(0, 1);
    if (!initialised) {
        seed();
    }
    int32_t random = booldistribution(generator);
    if (random == 1) {
        return true;
    } else {
        return false;
    }
}

// Returns a randomly generated integer, in the 0-2147483647 range
int32_t Random::randInt() {
    distribution = std::uniform_int_distribution<int32_t>();
    if (!initialised) {
        seed();
    }
    int32_t random = distribution(generator);
    return random;
}

// Returns a randomly generated integer, in the iStart-iEnd range
int32_t Random::randInt(const int32_t iStart, const int32_t iEnd) {
    if (checkInterval(iStart, iEnd)) {
        distribution = std::uniform_int_distribution<int32_t>(iStart, iEnd);
    } else {
        distribution = std::uniform_int_distribution<int32_t>(iEnd, iStart);
    }

    if (!initialised) {
        seed();
    }
    int32_t random = distribution(generator);
    return random;
}

// Returns a randomly generated double, in the 0-DBL_MAX range
double Random::randReal() {
    realdistribution = std::uniform_real_distribution<double>(0, DBL_MAX);
    if (!initialised) {
        seed();
    }
    double random = realdistribution(generator);
    return random;
}

// Returns a randomly generated double, in the iStart-iEnd range
double Random::randReal(const double iStart, const double iEnd) {
    if (checkInterval(iStart, iEnd)) {
        realdistribution = std::uniform_real_distribution<double>(iStart, iEnd);
    } else {
        realdistribution = std::uniform_real_distribution<double>(iEnd, iStart);
    }

    if (!initialised) {
        seed();
    }
    double random = realdistribution(generator);
    return random;
}