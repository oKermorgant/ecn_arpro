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
Individual geneticAlgo()
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

  Individual best;

  while(iter < max_iter && iter_same < max_same)
  {
    std::sort(population.begin(), population.end());
    best = population[0];

    if(best.cost == best_cost)
      iter_same++;
    else
    {
      std::cout << best.cost << " beaten after " << iter_same << " generations\n";
      best_cost = best.cost;

      iter_same = 0;
    }

    std::array<Individual, n> new_pop{population};

    for(int idx = keep; idx < n/2; ++idx)
    {
      const auto [n1,n2] = differentRandom(n); {}
      new_pop[idx] = std::min(population[n1], population[n2]);
    }

    // crossing
    for(int idx = n/2; idx < n; ++idx)
    {
      const auto [n1,n2] = differentRandom(n/2); {}

      new_pop[idx] = new_pop[n1].cross(new_pop[n2]);
      new_pop[idx].mutate();
    }

    population = new_pop;
    iter++;
  }


  std::cout << "Stop after " << iter << "\n";
  return best;
}


#endif // GENETIC_ALGO_H
