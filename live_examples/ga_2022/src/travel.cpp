#include "travel.h"
#include <yaml-cpp/yaml.h>
#include <numeric>
#include <rand_range.h>

Cities Travel::cities;
Distances Travel::distances;
size_t Travel::n;
size_t Travel::created{};
size_t Travel::copied{};

void Travel::load()
{
  auto config{YAML::LoadFile("../tsp.yaml")};
   cities = config["cities"].as<std::vector<std::string>>();
   for(int city = 0; city < cities.size(); ++city)
   {
     distances.push_back(config[city].as<std::vector<int>>());
   }
   n = cities.size();
}

void Travel::computeCost()
{
  cost = distances[order.front()][order.back()];
  for(size_t city = 0; city < n-1; ++city)
    cost += distances[order[city]][order[city+1]];
}

void Travel::randomize()
{
  std::iota(order.begin(), order.end(), 0);
  std::random_shuffle(order.begin(), order.end());
  computeCost();
}

void Travel::crossAndMutate(const Travel &p1, const Travel &p2)
{
  const auto cut{randRange(2, n-3)};
  std::copy(p1.order.begin(), p1.order.begin()+cut, order.begin());

  const auto last{p1.order[cut-1]};
  auto order_copy{p2.order};
  const auto start{std::find(order_copy.begin(), order_copy.end(), last)};
  std::rotate(order_copy.begin(), start, order_copy.end());

  auto current{cut};
  for(auto city: order_copy)
  {
    if(std::find(order.begin(), order.begin()+cut, city) == order.begin()+cut)
    {
      order[current] = city;
      current++;
    }
  }

  const auto [n1, n2] = differentRandomNumbers(0, n-1); {}
  std::swap(order[n1], order[n2]);

  computeCost();
}

/*
Travel Travel::crossAndMutate(const Travel &other) const
{
  Travel crossing;

  const auto cut{randRange(2, n-3)};
  std::copy(order.begin(), order.begin()+cut, crossing.order.begin());

  const auto last{order[cut-1]};
  auto order_copy{other.order};
  const auto start{std::find(order_copy.begin(), order_copy.end(), last)};
  std::rotate(order_copy.begin(), start, order_copy.end());

  auto current{cut};
  for(auto city: order_copy)
  {
    if(std::find(order.begin(), order.begin()+cut, city) == order.begin()+cut)
    {
      crossing.order[current] = city;
      current++;
    }
  }

  const auto [n1, n2] = differentRandomNumbers(0, n-1); {}
  std::swap(crossing.order[n1], crossing.order[n2]);

  crossing.computeCost();

  return crossing;
}
*/
