#ifndef RAND_UTILS_H
#define RAND_UTILS_H


#include <random>

double rand_double(double min = 0, double max = 1)
{
  //static std::random_device rd;  // Will be used to obtain a seed for the random number engine
  static std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> dis(min, max);
  return dis(gen);
}


#endif // RAND_UTILS_H
