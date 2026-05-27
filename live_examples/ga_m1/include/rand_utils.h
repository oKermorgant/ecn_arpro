#ifndef RAND_UTILS_H
#define RAND_UTILS_H

#include <random>

double rand_double(double min = 0, double max = 1)
{
  //static std::random_device rd;  // Will be used to obtain a seed for the random number engine
  static thread_local std::default_random_engine gen; // Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> dis(min, max);
  return dis(gen);
}

std::tuple<int, int> differentRandomNumbers(int max)
{
  static std::default_random_engine gen;
  std::uniform_int_distribution dis(0, max);

  // TODO check max value for feasability

  const auto n1{dis(gen)};
  auto n2{dis(gen)};
  while(n2 == n1)
    n2 = dis(gen);

  return {n1, n2};
}




#endif // RAND_UTILS_H
