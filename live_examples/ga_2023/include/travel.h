#ifndef TRAVEL_H
#define TRAVEL_H

#include <random>
#include <iostream>
#include <algorithm>
#include <yaml-cpp/yaml.h>

class Travel
{

public:

  using Cities = std::vector<std::string>;
  using Distances = std::vector<std::vector<int>>;
  static inline Cities cities;
  static inline Distances distances;
  static inline size_t n;


  static inline std::default_random_engine engine;
  static inline std::uniform_real_distribution<double> range{-5, 5};
  double cost;

  void computeCost()
  {

  }
public:

  static void load()
  {
    auto config{YAML::LoadFile("../tsp.yaml")};
    cities = config["cities"].as<std::vector<std::string>>();
    for(int city = 0; city < cities.size(); ++city)
    {
      distances.push_back(config[city].as<std::vector<int>>());
    }
    n = cities.size();
  }

  void randomize()
  {

  }

  auto getCost() const
  {
    return cost;
  }


  Travel crossAndMutate(const Travel &other) const
  {
    Travel child;
    child.mutate();
    return child;
  }

  void mutate()
  {
    computeCost();
  }

  void print() const
  {

  }

};



#endif // TRAVEL_H
