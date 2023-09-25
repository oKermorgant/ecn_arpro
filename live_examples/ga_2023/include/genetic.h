#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <algorithm>
#include <random>
#include <rand_range.h>

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

  for(auto &individual: population)
    individual.randomize();

  const uint max_iter = 100;
  uint iter = 0;

  while(iter < max_iter)
  {

    //auto best = *std::min_element(population.begin(), population.end());

    std::nth_element(population.begin(),
                     population.begin()+keep_best,
                     population.end());

    std::vector<Individual> new_population{population.begin(), population.begin()+keep_best};

    while(new_population.size() < pop_size/2)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size-1);  {}
      new_population.push_back(std::min(population[n1], population[n2]));
    }

    while(new_population.size() < pop_size)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size/2-1);  {}
      new_population.push_back(new_population[n1].crossAndMutate(new_population[n2]));
    }

    population = new_population;

    iter++;
  }

  return *std::min_element(population.begin(), population.end());

}

#endif // GENETIC_H
