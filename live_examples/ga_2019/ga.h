#ifndef GA_H
#define GA_H

#include <algorithm>
#include <tuple>
#include <iostream>
#include <vector>

template <class T>
bool operator<(const T&xy1, const T &xy2)
{
  return xy1.cost() < xy2.cost();
}

template <class T>
bool operator==(const T &xy1, const T &xy2)
{
  return xy1.cost() == xy2.cost();
}

std::tuple<uint, uint> two_random_numbers(uint n)
{
  const uint n1 = rand() % n;
  uint n2 = rand() % n;

  while(n1 != n2)
    n2 = rand() % n;

  return {n1,n2};
}

template <class T>
void genetic_algo(T &best)
{
  const uint pop_size = 500;
  const uint keep = 10;
  const uint max_iter = 30;

  std::vector<T> population(pop_size);

  uint iter(0), iter_total(0);

  for(auto &v: population)
    v.randomize();


  std::nth_element(population.begin(),
                   population.begin() + keep,
                   population.end());

  best = *std::min_element(population.begin(),
                           population.begin()+keep);

  std::vector<T> selection(pop_size/2-keep);

  while(iter < max_iter)
  {
    iter_total++;

    for(auto & indiv: selection)
    {
      const auto [n1,n2] = two_random_numbers(pop_size); {}
      indiv = std::min(population[n1],population[n2]);
    }

    std::copy(selection.begin(), selection.end(),
              population.begin() + keep);


    for(uint i = 0; i < pop_size/2; ++i)
    {
      const auto [n1,n2] = two_random_numbers(pop_size/2); {}

      T& new_indiv = population[pop_size/2+i];
      new_indiv.cross(population[n1], population[n2]);
      new_indiv.mutate();
    }

    std::nth_element(population.begin(),
                     population.begin() + keep,
                     population.end());

    auto new_best = *std::min_element(population.begin(),
                                      population.begin()+keep);

    if(new_best == best)
    {
      iter++;
    }
    else
    {
      iter = 0;
      best = new_best;
    }

  }
  std::cout << "Found in " << iter_total << " iterations\n";
}


#endif // GA_H
