#ifndef GA_H
#define GA_H

#include <algorithm>
#include <rand_range.h>
#include <iostream>

//#define FUZZY_SELECT




template <class Individual>
Individual genetic()
{
  const auto pop_size{3000};
  const auto half_pop{pop_size/2};
  const auto max_iter{10000};
  const auto max_iter_seq{max_iter/2};

  std::array<Individual, pop_size> population;
  for(auto &indiv: population)
    indiv.randomize();

#ifdef FUZZY_SELECT
  const auto keep_best{0};
  std::array<double, pop_size> rel_fitness;
#else
  const auto keep_best{30};
#endif
  std::array<Individual, pop_size/2-keep_best> winners;
  auto iter{0};
  auto iter_seq{0};

#ifdef FUZZY_SELECT      
  const auto reorder = [&]()
  {
    return std::min_element(population.begin(), population.end());
  };
  const auto worst_cost = std::abs(std::accumulate(population.begin(), population.end(), 0.,
                                         [&](const double &s, const Individual &indiv)
                                           {return s+indiv.cost;}));
  std::cout << "worst: " << worst_cost << std::endl;
  const auto fitness = [=](const Individual &indiv)
  {
    return worst_cost - indiv.cost;
  };
  const auto sumFitness = [&](const double &s, const Individual &indiv)
  {
    return s + fitness(indiv);
  };

#else
  const auto reorder = [&]()
  {
    std::nth_element(population.begin(), population.begin() + keep_best, population.end());
    return std::min_element(population.begin(), population.begin()+keep_best);
  };
#endif

  auto best = reorder();
  auto best_cost = best->getCost();

  while(iter < max_iter && iter_seq < max_iter_seq)
  {
#ifdef FUZZY_SELECT

    std::transform(population.begin(), population.end(), rel_fitness.begin(),
                   [&](const auto &indiv){return fitness(indiv);});
    const auto total = std::accumulate(rel_fitness.begin(), rel_fitness.end(), 0.);
    std::partial_sum(rel_fitness.begin(), rel_fitness.end(), rel_fitness.begin());
    for(auto &winner: winners)
    {
      const auto r{randRange(0., total)};
      const auto cut{std::lower_bound(rel_fitness.begin(), rel_fitness.end(), r)};
      winner = population[std::distance(rel_fitness.begin(), cut)];
    }

#else
    for(auto &winner: winners)
    {
      const auto [n1,n2] = differentRandomNumbers(keep_best, pop_size-1); {}
      winner = std::min(population[n1], population[n2]);
    }
#endif

    std::copy(winners.begin(), winners.end(),
              population.begin()+keep_best);

    for(auto crossed = population.begin()+pop_size/2;
        crossed != population.end();
        ++crossed)
    {
      const auto [n1,n2] = differentRandomNumbers(0, pop_size/2-1); {}
      crossed->crossAndMutate(population[n1], population[n2]);
    }

    best = reorder();

    if(const auto new_cost{best->getCost()}; new_cost < best_cost)
    {
      best_cost = new_cost;
      iter_seq = 0;
    }
    else
    {
      iter_seq++;
    }

    iter++;
  }
  return *best;
}






#endif // GA_H
