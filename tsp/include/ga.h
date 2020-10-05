#ifndef GALG_H
#define GALG_H

#include <vector>
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <rand_util.h>

template<class T>
bool operator<(const T &i1, const T& i2)
{
  return i1.evaluate() < i2.evaluate();
}

// run genetic algorithm on the given class
template<class T> T solveGA()
{    
  const uint keep_best(5);
  const uint iter_out(30);
  const uint pop_size(500);
  const auto half_pop_size(pop_size/2);

  // init first population from random individuals
  std::vector<T> population(pop_size);
  for(auto &indiv: population)
    indiv.randomize();

  std::nth_element(population.begin(), population.begin()+keep_best,
                   population.end());
  auto best = *std::min_element(population.begin(),
                                population.begin()+keep_best);
  double best_cost = best.evaluate();

  // loop until exit conditions
  uint iter=0;
  std::vector<T> selected(pop_size/2-keep_best);

  while(iter++ < iter_out)
  {
    // selection, 1 vs 1 tournament to fill half of the population
    for(auto & indiv: selected)
    {
      const auto [n1, n2] = twoDifferentRandoms(pop_size);{}
      indiv = std::min(population[n1], population[n2]);
    }

    // put new elements after elites
    std::copy(selected.begin(), selected.end(),
              population.begin()+keep_best);

    // crossing and mutation to fill other half of the new pop
    for(uint i=half_pop_size;i<pop_size;++i)
    {
      const auto [n1, n2] = twoDifferentRandoms(pop_size);{}
      // cross between parents + compute cost
      population[i].crossAndMutate(population[n1],population[n2]);
    }

    // re-sort from new costs
    std::nth_element(population.begin(), population.begin()+keep_best,
                     population.end());

    if(best.evaluate() < best_cost)
    {
      iter = 0;
      best_cost = best.evaluate();
    }
    else
      iter++;
  }
  return best;
}


#endif // GALG_H
