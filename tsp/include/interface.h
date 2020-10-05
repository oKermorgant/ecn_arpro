#ifndef GA_INTERFACE_H
#define GA_INTERFACE_H

#include <yaml-cpp/yaml.h>
#include <vector>
#include <iostream>

struct Interface
{
  Interface(std::string filename)
  {
    filepath = "../data/" + filename;
    YAML::Node data = YAML::LoadFile(filepath);
    cities = data["cities"].as<std::vector<std::string>>();
    const auto N = cities.size();
    distances.resize(N);
    for(uint i=0;i<N;++i)
    {
      distances[i].resize(N);
      for(uint j=0;j<N;++j)
        distances[i][j] = data[i][j].as<double>();
    }
  }

  int dist(int city1, int city2) const
  {
    return distances[city1][city2];
  }

  void print(std::vector<int> ordering)
  {
    int cost(0);

    for(uint i=0;i<ordering.size()-1;++i)
    {
      cost += dist(ordering[i], ordering[i+1]);
      std::cout << cities[ordering[i]] << " -> ";
    }

    // close cycle
    cost += dist(ordering.front(), ordering.back());
    std::cout << cities[ordering.back()];

    std::cout <<  " -> " << cities[ordering.front()];
    std::cout << std::endl;
    std::cout << "  -> distance = " << cost << " km" << std::endl << std::endl;
  }

  void display(std::vector<int> ordering)
  {
    // display map just for fun
    std::stringstream ss;
    ss << "python ../data/show_travel.py " << filepath;
    for(auto i: ordering)
      ss << " " << i;
    system(ss.str().c_str());
  }

  std::vector<std::vector<int>> distances;
  std::vector<std::string> cities;
  std::string filepath;
};


#endif // GA_INTERFACE_H
