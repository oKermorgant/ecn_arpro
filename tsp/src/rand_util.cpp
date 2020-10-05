#include <rand_util.h>
#include <stdlib.h>

int randint(int max)
{
  return rand() % max;
}

std::tuple<uint, uint> twoDifferentRandoms(int max)
{
  const int n1 = randint(max);
  int n2 = randint(max);
  while(n1 == n2)
    n2 = randint(max);
  return {n1,n2};
}

double randBetween(double min, double max)
{
    const double rand01 = ((double) rand() ) / RAND_MAX;
    return min + (max-min)*rand01;
}
