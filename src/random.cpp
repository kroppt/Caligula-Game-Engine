#define _NUS_RAND_IMPL_C 1
#include "random.hpp"
#include <random>


std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> normalizedIntervalUniformDist(1.0, 10.0);

extern inline double getRandomNormal(void){ return normalizedIntervalUniformDist(mt);}