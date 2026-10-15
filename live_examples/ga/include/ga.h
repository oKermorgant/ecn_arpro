#ifndef GA_H
#define GA_H

#include <algorithm>
#include <point.h>
#include <random>
#include <vector>


bool operator<(const Point &p1, const Point &p2)
{
  return p1.getCost() < p2.getCost();
}

std::tuple<int,int> twoDifferentRandomNumbers(int min, int max)
{
  static std::mt19937 generator;
  auto dist1{std::uniform_int_distribution(min, max)};
  auto dist2{std::uniform_int_distribution(min, max-1)};

  const auto n1{dist1(generator)};
  const auto n2{dist2(generator)};

    if(n1 == n2)
    return {n1, n2+1};

  return {n1,n2};

}


Point optimize()
{
  const auto popSize{100};
  const auto elitism{popSize/10};
  const auto maxIter{100};
  const auto maxSame{maxIter/3};

  std::vector<Point> population(popSize);
  for(auto &point: population)
    point.randomize();

  auto iter{0};
  auto iter_same{0};
  Point overallBest;
  overallBest.randomize();
  Point best = *std::min_element(population.begin(),
                               population.end());
  best.print();
  while(iter ++ < maxIter and iter_same < maxSame)
  {
    std::nth_element(population.begin(),
                     population.begin()+elitism,
                     population.end());

    best = *std::min_element(population.begin(),
                             population.begin()+elitism);

    std::vector<Point> new_pop(population.begin(),
                               population.begin()+elitism);
    new_pop.reserve(popSize);

    for(auto i = elitism; i < popSize/2; ++i)
    {
      const auto [n1,n2] = twoDifferentRandomNumbers(0, popSize-1);
      new_pop.push_back(std::min(population[n1], population[n2]));
    }

    for(auto i = 0; i < popSize/2; ++i)
    {
      const auto [n1,n2] = twoDifferentRandomNumbers(0, popSize/2-1);
      Point p;
      p.crossFrom(new_pop[n1], new_pop[n2]);
      p.mutate();
      new_pop.push_back(p);
    }

    population = new_pop;

    const auto new_best = *std::min_element(population.begin(),
                                            population.end());
    if(new_best < overallBest)
    {
      overallBest = new_best;
      iter_same = 0;
    }
    else
    {
      iter_same++;
    }


  }

  std::cout << "Exit after " << iter << " iterations\n";
  return overallBest;
}

#endif // GA_H
