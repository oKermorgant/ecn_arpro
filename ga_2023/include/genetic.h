#ifndef GENETIC_H
#define GENETIC_H

#include <algorithm>

template <class Individual>
Individual geneticOptim()
{

  const auto pop_size{500};
  const auto keep{50};
  const auto max_iter{100};

  std::vector<Individual> population(pop_size);
  for(auto &indiv: population)
  {
    indiv.randomize();
  }
  

  Individual best;
  auto iter{0};
  while(iter < max_iter)
  {
    iter++;

    std::partial_sort(population.begin(),
                      population.begin()+keep,
                      population.end());

    std::vector<Individual> new_population;
    std::copy(population.begin(), population.begin()+keep,
              std::back_inserter(new_population));

    for(int i = keep; i < pop_size/2; ++i)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size-1); {}

      new_population.push_back(std::min(population[n1],population[n2]));
    }


    for(int i = pop_size/2; i < pop_size; ++i)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size/2-1); {}



      new_population.push_back(new_population[n1].cross(new_population[n2]));
      new_population.back().mutate();
    }
    population = new_population;
    best = *std::min_element(population.begin(), population.end());
    best.print();
  }
  // TODO return the best one

  return best;
}

#endif // GENETIC_H
