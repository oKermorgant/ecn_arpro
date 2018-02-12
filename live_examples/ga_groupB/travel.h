#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <algorithm>

class Travel
{
  public:

    Travel()
    {
        for(int city_index = 0; city_index < distances.size(); ++city_index)
        ordering.push_back(city_index);
    }

    void randomize()
    {
        std::random_shuffle(ordering.begin(), ordering.end());
        computeCost();
    }

    void computeCost()
    {
        cost = 0;
        for(int i = 0; i < ordering.size(); ++i)
        {
            int departure = ordering[i];
            int arrival = ordering[(i+1) % ordering.size()];
            cost += distances[departure][arrival];
        }
    }

    void cross(Travel t1, Travel t2)
    {
        const int n = ordering.size();

        int cut = rand() % (n-4) + 2;

        for(int i = 0; i < cut; ++i)
            ordering[i] = t1.ordering[i];

        int idx = 0;
        for(idx = 0; idx < n; ++idx)
        {
            if(t2.ordering[idx] == t1.ordering[cut-1])
                break;
        }

        for(int i = idx+1; i < idx + n; ++i)
        {
            int city_index = t2.ordering[i % n];
            if(std::count(ordering.begin(),
                          ordering.begin() + cut,
                          city_index)
                    == 0)
            {
               ordering[cut] = city_index;
               cut++;
            }
        }


        mutate();
    }

    void mutate()
    {
        int n1 = rand() % ordering.size();
        int n2 = rand() % ordering.size();

        std::swap(ordering[n1], ordering[n2]);

        computeCost();
    }

    void print(YAML::Node cities)
    {
        for(auto city_index: ordering)
            std::cout << cities[city_index] << " -> ";
        std::cout << cities[ordering.front()] << std::endl;
        std::cout << "Overall distance: " << cost  << std::endl;
    }


    bool operator==(Travel other)
    {
        for(int i = 0; i < ordering.size(); ++i)
        {
            if(ordering[i] != other.ordering[i])
                return false;
        }
        return true;
    }


    double cost;
    std::vector<int> ordering;
    static std::vector<std::vector<int>> distances;

};



#endif // TRAVEL_H
