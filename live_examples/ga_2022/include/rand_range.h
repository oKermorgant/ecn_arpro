#ifndef RAND_RANGE_H
#define RAND_RANGE_H

#include <random>

namespace
{
template <typename T>
inline auto randRange(T distribution)
{
  static std::default_random_engine generator;
  return distribution(generator);
}

}

inline auto randRange(int min, int max)
{
  return randRange(std::uniform_int_distribution(min, max));
}

inline auto randRange(double min, double max)
{
  return randRange(std::uniform_real_distribution(min, max));
}

inline std::pair<size_t, size_t> differentRandomNumbers(int min, int max)
{
  const auto n1{randRange(min, max)};
  auto n2{randRange(min, max)};
  while(n1 == n2)
    n2 = randRange(min, max);

  return {n1, n2};
}



#endif // RAND_RANGE_H
