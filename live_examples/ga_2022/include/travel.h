#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>
#include <string>
#include <iostream>
#include "individual.h"

using Cities = std::vector<std::string>;
using Distances = std::vector<std::vector<int>>;

class Travel : public Individual
{
  static Cities cities;
  static Distances distances;
  static size_t n;

  std::vector<size_t> order;

  void computeCost();

public:

  static void load(); 

  void crossAndMutate(const Travel &p1, const Travel &p2);

  inline Travel crossAndMutate(const Travel &other) const
  {
    Travel child;
    child.crossAndMutate(*this, other);
    return child;
  }

  void print() const
  {
    for(auto city: order)
      std::cout << cities[city] << " - ";
    std::cout << cost << " km\n" << std::endl;
  }

  void plot() const
  {
    std::string cmd = "python3 ../python/show_travel.py tsp.yaml";
    for(auto city: order)
      cmd += " " + std::to_string(city);
    [[maybe_unused]] auto out = system(cmd.c_str());
  }

  Travel() : order{std::vector<size_t>(n)} {}

  void randomize();


};

#endif // TRAVEL_H
