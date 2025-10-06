#ifndef RAND_UTILS_H
#define RAND_UTILS_H

#include <random>
#include <tuple>


double rand01()
{
  static std::default_random_engine engine;
  static std::uniform_real_distribution<double> unif(0,1);
  return unif(engine);
}

template <class T> T rand(T min, T max)
{
  return min + rand01()*(max-min);
}

std::pair<int, int> differentRandomNumbers(int max)
{

  const auto n1 = rand(0, max);
  auto n2 = rand(0, max-1);

  if(n1 == n2)
    n2++;

  return {n1, n2};
}

#endif // RAND_UTILS_H
