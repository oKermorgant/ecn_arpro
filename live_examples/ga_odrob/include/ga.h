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

  for(auto xy: population)
    xy.print();







  return XY();
}



#endif // GA_H
