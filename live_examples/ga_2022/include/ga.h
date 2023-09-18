#ifndef GA_H
#define GA_H

#include <algorithm>
#include <rand_range.h>
#include <iostream>

template <class Individual>
Individual genetic()
{
  const size_t pop_size{3000};
  const size_t keep_best{100};
  const auto max_iter{1000};

  std::vector<Individual> population(pop_size);
  for(auto &indiv: population)
    indiv.randomize();

  auto iter{0};

  std::nth_element(population.begin(), population.begin() + keep_best, population.end());
  auto best = *std::min_element(population.begin(), population.begin()+keep_best);


  while(iter < max_iter)
  {
    std::vector<Individual> new_population;
    for(int i = 0; i < keep_best; ++i)
      new_population.push_back(population[i]);


    while(new_population.size() < pop_size/2)
    {
      const auto [n1,n2] = differentRandomNumbers(keep_best, pop_size-1); {}
      new_population.push_back(std::min(population[n1], population[n2]));
    }

    while(new_population.size() < pop_size)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size/2-1); {}
      new_population.push_back(new_population[n1].crossAndMutate(new_population[n2]));
    }

    population = new_population;
    std::nth_element(population.begin(), population.begin()+keep_best, population.end());
    best = *std::min_element(population.begin(), population.begin()+keep_best);


   iter++;
  }
  return best;
}






#endif // GA_H
