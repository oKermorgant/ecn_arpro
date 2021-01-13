#ifndef GA_H
#define GA_H

#include <vector>
#include <algorithm>
#include <tuple>

int comparisons = 0;

template <class Indiv>
bool operator<(const Indiv& xy1,
               const Indiv& xy2)
{
  comparisons++;
  return xy1.eval() < xy2.eval();
}

int randint(int max)
{
  return rand() % max;
}

std::tuple<int,int> twoDifferentRandoms(int max)
{
  int n1 = randint(max);
  int n2 = randint(max);
  while(n1 == n2)
    n2 = randint(max);
  return {n1, n2};
}


template <class Indiv>
Indiv ga()
{
  const int pop_size(500);
  const int max_iter(40);

  const int elitism(30);

  std::vector<Indiv> population(pop_size);
  for(auto & indiv: population)
    indiv.randomize();

  int iter(0);
  double best_cost = std::numeric_limits<double>::max();
  std::nth_element(population.begin(),
                   population.begin() + elitism,
                   population.begin()+pop_size);
  auto best = std::min_element(population.begin(),
                              population.begin()+elitism);


  std::vector<Indiv> selection(pop_size/2-elitism);

  while(iter < max_iter)
  {
    // tournament
    for(auto &selected: selection)
    {
      auto [idx1,idx2] = twoDifferentRandoms(pop_size);
      selected = std::min(population[idx1], population[idx2]);
    }

    std::copy(selection.begin(), selection.end(),
              population.begin()+elitism);


    // generation
    for(int step = pop_size/2; step < pop_size; ++step)
    {
      auto [idx1, idx2] = twoDifferentRandoms(pop_size/2);
      population[step].cross(population[idx1], population[idx2]);
      population[step].mutate();
    }

    std::nth_element(population.begin(),
                     population.begin() + elitism,
                     population.begin()+pop_size);
    best = std::min_element(population.begin(),
                           population.begin()+elitism);

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
