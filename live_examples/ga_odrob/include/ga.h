#ifndef GA_H
#define GA_H

#include <cassert>
#include <xy.h>


XY optimize()
{
  const auto pop_size{50000};
  const auto elitism{pop_size/10};

  const auto max_iter{100};
  const auto max_iter_seq{max_iter};

  std::vector<XY> population(pop_size);

  for(auto &xy: population)
    xy.randomize();

  uint iter{0};
  uint iter_seq{0};
  auto best_cost{std::numeric_limits<double>::max()};
  while(iter < max_iter && iter_seq < max_iter_seq)
  {
    // TODO init new population from best elements
    // TODO improve perf for k-th best elements
    std::nth_element(population.begin(),
                      population.begin()+elitism,
                      population.end());

    std::vector<XY> new_pop;
    new_pop.reserve(pop_size);

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
    while(new_pop.size() < pop_size)
    {
      const auto [n1,n2] = differentRandomNumbers(pop_size/2);
      new_pop.push_back(new_pop[n1].cross(new_pop[n2]));
      new_pop.back().mutate();
    }

    population.swap(new_pop);
    //std::swap(population, new_pop);
    iter++;

    const auto best{std::min_element(population.begin(),
                                     population.end())};
    if(best->cost() < best_cost)
    {
      iter_seq = 0;
      best_cost = best->cost();
    }
    else
    {
      iter_seq++;
    }
  }

  // TODO return best element
  auto best = std::min_element(population.begin(),
                               population.end());
  return *best;
}



#endif // GA_H
