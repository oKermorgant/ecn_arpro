#ifndef GA_H
#define GA_H

#include "xy.h"
#include <vector>
#include <algorithm>

int comparisons = 0;

bool operator<(const XY& xy1,
               const XY& xy2)
{
  comparisons++;
return xy1.eval() < xy2.eval();
}


XY ga()
{
  const int pop_size(500);
  const int max_iter(40);

  const int elitism(30);

  std::vector<XY> population(pop_size + (pop_size/2-elitism));
  for(auto & indiv: population)
    indiv.randomize();


  const auto elitismRun = [&]()
  {
    std::nth_element(population.begin(),
                     population.begin() + elitism,
                     population.begin()+pop_size);
    return std::min_element(population.begin(),
                            population.begin()+elitism);
  };

  int iter(0);
  double best_cost = std::numeric_limits<double>::max();
  auto best = elitismRun();

  while(iter < max_iter)
  {
    // tournament
    for(int step = pop_size; step < population.size(); ++step)
    {
      int idx1(rand() % pop_size);
      int idx2(rand() % pop_size);

      population[step] = std::min(population[idx1], population[idx2]);
    }
    std::copy(population.begin()+pop_size, population.end(),
              population.begin()+elitism);

    // generation
    for(int step = pop_size/2; step < pop_size; ++step)
    {
      int idx1(rand() % pop_size/2);
      int idx2(rand() % pop_size/2);

      //population[step] = population[idx1].cross(population[idx2]);
      population[step].cross(population[idx1], population[idx2]);
      population[step].mutate();
    }

    best = elitismRun();

    if(best->eval() < best_cost)
    {
      best_cost = best->eval();
      iter = 0;
    }
    else
      iter++;
  }

  return *best;
}


#endif // GA_H
