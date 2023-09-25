#ifndef TRAVEL_H
#define TRAVEL_H

#include <random>
#include <iostream>
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <numeric>
#include <rand_range.h>

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


  int cost;
  std::vector<int> sequence;

  void computeCost()
  {
    cost = distances[sequence.front()][sequence.back()];

    for(int i = 0; i < n-1; ++i)
    {
      cost += distances[sequence[i]][sequence[i+1]];
    }



  }
public:

  Travel()
  {
    sequence.resize(n);
    std::iota(sequence.begin(), sequence.end(), 0);
  }



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
    std::random_shuffle(sequence.begin(), sequence.end());
    computeCost();
  }

  auto getCost() const
  {
    return cost;
  }


  Travel crossAndMutate(const Travel &other) const
  {
    Travel child;

    const auto cut = randRange(1, n-2);
    const auto last = sequence[cut-1];

    std::copy(sequence.begin(), sequence.begin()+cut,
              child.sequence.begin());

    const auto where = std::find(other.sequence.begin(), other.sequence.end(),
                           last);
    const auto offset = std::distance(other.sequence.begin(), where) + 1;

    auto current = cut;
    for(int i = offset; i < offset + n; ++i)
    {
      const auto city = other.sequence[i % n];
      if(std::find(sequence.begin(), sequence.begin()+cut, city) == sequence.begin()+cut)
      {
        child.sequence[current] = city;
        current++;
      }
    }

    child.mutate();
    return child;
  }

  void mutate()
  {
    // pick two different random numbers between 0 and n-1
    const auto [n1, n2] = differentRandomNumbers(0, n-1); {}

    std::swap(sequence[n1], sequence[n2]);

    computeCost();
  }

  void print() const
  {
    for(const auto &city: sequence)
    {
      std::cout << cities[city] << " -> ";
    }

    std::cout << " distance: " << cost << " km\n" << std::endl;
  }

  void plot() const
  {
    std::string cmd = "python3 ../python/show_travel.py tsp.yaml";
    for(auto city: sequence)
      cmd += " " + std::to_string(city);
    [[maybe_unused]] auto out = system(cmd.c_str());
  }

};



#endif // TRAVEL_H
