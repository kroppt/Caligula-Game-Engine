#ifndef NUS_RANDOM_H
#define NUS_RANDOM_H 1
#ifndef __cplusplus
#error  This is C++.
#endif 
#include <stdint.h>
#include <random>

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_real_distribution<double> normalizedIntervalUniformDist;
#ifndef _NUS_RAND_IMPL_C
inline double getRandomNormal(void){ return normalizedIntervalUniformDist(mt);} 
#endif
#endif