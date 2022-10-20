#ifndef GA_H
#define GA_H

#include <algorithm>
#include <rand_range.h>
#include <iostream>



template <class Individual>
Individual genetic()
{
  const size_t pop_size{500};
  const size_t keep_best{30};
  const auto half_pop{pop_size/2};
  const auto max_iter{100};
  const auto max_iter_seq{30};

  std::array<Individual, pop_size> population;
  std::array<Individual, pop_size/2-keep_best> winners;
  auto iter{0};
  auto iter_seq{0};

  const auto reorder = [&]()
  {
    std::nth_element(population.begin(), population.begin() + keep_best, population.end());
    return std::min_element(population.begin(), population.begin()+keep_best);
  };

  auto best = reorder();
  auto best_cost = best->getCost();

  while(iter < max_iter && iter_seq < max_iter_seq)
  {
    for(auto &winner: winners)
    {
      const auto [n1,n2] = differentRandomNumbers(keep_best, pop_size-1); {}
      winner = std::min(population[n1], population[n2]);
    }

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
