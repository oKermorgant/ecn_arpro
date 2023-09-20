#ifndef GENETIC_H
#define GENETIC_H

#include <xy.h>
#include <vector>

XY genetic(uint pop_size)
{

  std::vector<XY> population(pop_size);

  for(auto &individual: population)
    individual.randomize();

  for(auto indiv: population)
    indiv.print();



}

#endif // GENETIC_H
