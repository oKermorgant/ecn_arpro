#ifndef GA_H
#define GA_H

#include <xy.h>


XY optimize()
{
  const auto pop_size{10};
  const auto elitism{pop_size/10};
  const auto max_iter{100};

  std::vector<XY> population(pop_size);

  for(auto &xy: population)
    xy.randomize();

  uint iter{0};
  while(iter < max_iter)
  {
    // TODO init new population from best elements
    // TODO improve perf for k-th best elements
    std::sort(population.begin(), population.end());

    std::vector<XY> new_pop;

    // elitism part
    for(int i = 0; i < elitism; ++i)
      new_pop.push_back(population[i]);

    // TODO tournament
    while(new_pop.size() < pop_size/2)
    {
      const auto [n1,n2] = differentRandomNumbers(pop_size);
      new_pop.push_back(std::min(population[n1], population[n2]));
    }

    // TODO crossovers and mutations



  }

  // TODO return best element
  return population.front();
}



#endif // GA_H
