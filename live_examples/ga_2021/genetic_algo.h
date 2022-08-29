#ifndef GENETIC_ALGO_H
#define GENETIC_ALGO_H

#include <array>
#include <random>
#include <iostream>

#include <algorithm>

std::pair<int, int> differentRandom(int n)
{
  static std::default_random_engine engine;

  std::uniform_int_distribution<> dice(0,n-1);
  std::uniform_int_distribution<> dice2(0,n-2);

  const auto n1{dice(engine)};
  auto n2{dice2(engine)};

  if(n1 == n2)
    n2++;

  return {n1, n2};
}

template <class Individual>
bool operator<(const Individual &indiv1, const Individual &indiv2)
{
  return indiv1.cost < indiv2.cost;
}

template <class Individual>
void geneticAlgo(Individual &best)
{
  const int n{500};
  const int keep{n/10};
  const int max_iter{100};
  const int max_same{30};

  std::array<Individual, n> population;
  for(auto &indiv: population)
    indiv.randomize();

  auto iter{0};
  auto iter_same{0};
  double best_cost{0};

  while(iter < max_iter && iter_same < max_same)
  {
    std::nth_element(population.begin(), population.begin()+keep, population.end());
    best = *std::min_element(population.begin(), population.begin()+keep);

    if(best.cost == best_cost)
      iter_same++;
    else
    {
      std::cout << best.cost << " beaten after " << iter_same << " generations\n";
      best_cost = best.cost;

      iter_same = 0;
    }

    std::array<Individual, n/2-keep> winners;

    for(auto &winner: winners)
    {
      const auto [n1,n2] = differentRandom(n); {}
      winner = std::min(population[n1], population[n2]);
    }

    std::copy(winners.begin(), winners.end(), population.begin()+keep);

    // crossing
    for(int idx = n/2; idx < n; ++idx)
    {
      const auto [n1,n2] = differentRandom(n/2); {}

      population[idx].cross(population[n1], population[n2]);
      population[idx].mutate();
    }

    iter++;
  }

  std::cout << "Stop after " << iter << "\n";

}


#endif // GENETIC_ALGO_H
