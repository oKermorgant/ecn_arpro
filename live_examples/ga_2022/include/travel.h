#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>
#include <string>
#include <iostream>

using Cities = std::vector<std::string>;
using Distances = std::vector<std::vector<int>>;

class Travel
{
  static Cities cities;
  static Distances distances;
  static size_t n;

  static size_t created;
static size_t copied;

  std::vector<size_t> order;
  int cost;

  void computeCost();

public:



  static void load();

  bool operator<(const Travel &other) const
  {
    return cost < other.cost;
  }

  //Travel crossAndMutate(const Travel &other) const;
  void crossAndMutate(const Travel &p1, const Travel &p2);

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
    system(cmd.c_str());
  }

  Travel() : order{std::vector<size_t>(n)}
  {
    created++;
    randomize();
  }

  Travel(const Travel &src) : order{src.order}, cost{src.cost}
  {
    copied++;
  }

  ~Travel()
  {

  }

  void randomize();

  auto getCost() const {return cost;}

  static void summary()
  {
    std::cout << "Created: "<< created <<
                 "/ copied: "<< copied << std::endl;
  }


};

#endif // TRAVEL_H
