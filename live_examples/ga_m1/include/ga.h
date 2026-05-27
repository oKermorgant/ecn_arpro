#ifndef GA_H
#define GA_H

#include <xy.h>
#include <execution>

XY optimize()
{
  const uint pop_size{10000};
  const uint max_iter{100};
  const uint elitism{pop_size/10};

  std::vector<XY> population(pop_size);
  std::for_each(std::execution::par_unseq,
      population.begin(), population.end(),[](auto &candidate)
                {candidate.randomize();});

  uint iter{0};

  while(iter < max_iter)
  {
    std::vector<XY> new_pop;
    new_pop.reserve(pop_size);

    std::partial_sort(population.begin(), population.begin()+elitism, population.end());

    // elitism
    std::copy(population.begin(), population.begin()+elitism,
              std::back_inserter(new_pop));

    // tournament



    while(new_pop.size() < pop_size/2)
    {
      const auto [n1, n2] = differentRandomNumbers(pop_size-1);
      new_pop.push_back(std::min(population[n1], population[n2]));
    }

    // crossover
    while(new_pop.size() < pop_size)
    {
      const auto [n1, n2] = differentRandomNumbers(pop_size/2-1);
      auto new_indiv = new_pop[n1].crossAndMutate(new_pop[n2]);
      new_pop.push_back(new_indiv);
    }

    std::swap(population, new_pop);
    iter++;
  }

  auto best = std::min_element(population.begin(), population.end());

  return *best;
}

#endif // GA_H
