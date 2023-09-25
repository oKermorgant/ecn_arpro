#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <algorithm>
#include <random>
#include <rand_range.h>
#include <iostream>

template <class Individual>
bool operator<(const Individual &xy1, const Individual &xy2)
{
  return xy1.getCost() < xy2.getCost();
}

template <class Individual>
Individual genetic(const uint pop_size)
{

  std::vector<Individual> population(pop_size);

  const auto keep_best = pop_size/10;
  std::vector<Individual> selection(pop_size/2 - keep_best);

  for(auto &individual: population)
    individual.randomize();

  const uint max_iter = 100;
  const uint max_iter_best = 30;

  uint iter = 0;
  uint iter_best = 0;

  auto best = *std::min_element(population.begin(), population.end());

  while(iter < max_iter && iter_best < max_iter_best)
  {
    std::nth_element(population.begin(),
                     population.begin()+keep_best,
                     population.end());


    for(auto &selected: selection)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size-1);  {}
      selected = std::min(population[n1], population[n2]);
    }

    std::copy(selection.begin(), selection.end(), population.begin()+keep_best);

    for(int i = pop_size/2; i < pop_size; ++i)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size/2-1);  {}
      population[i] = population[n1].crossAndMutate(population[n2]);
    }

    auto new_best = *std::min_element(population.begin(), population.end());
    if(new_best < best)
    {
      iter_best = 0;
      best = new_best;
    }
    else
    {
      iter_best++;
    }

    iter++;
  }

  std::cout << "Exit after " << iter << " iterations" << std::endl;

  return best;

}

#endif // GENETIC_H
