#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <algorithm>


class Travel
{
  public:
        Travel()
        {
            n = distances.size();
            order.resize(n);
            for(int i = 0; i < n; ++i)
                order[i] = i;
        }

        bool operator==(const Travel & other)
        {
            for(int i = 0; i < n; ++i)
            {
                if(order[i] != other.order[i])
                    return false;
            }
            return true;
        }

        void print(const YAML::Node &cities)
        {
            for(const auto &idx: order)
                std::cout << cities[idx] << " -> ";
            std::cout << cities[order.front()] << std::endl;
            std::cout << "cost -> " << cost << std::endl;
        }

        void randomize()
        {
            std::random_shuffle(order.begin(), order.end());
            computeCost();
        }

        void computeCost()
        {
            cost = 0;
            for(int i = 0; i < n; ++i)
            {
                int departure = order[i];
                int arrival = order[(i+1)%n];
                cost += distances[departure][arrival];
            }
        }

        void crossAndMutate(const Travel & t1, const Travel & t2)
        {
            int cut = rand() % (n-4) + 2;
            for(int i = 0; i < cut; ++i)
                order[i] = t1.order[i];

            int idx;
            for(idx = 0; idx < n; ++idx)
                if(t2.order[idx] == order[cut-1])
                    break;

            for(int i = idx+1; i < idx+n; ++i)
            {
                int city = t2.order[i % n];
                if(std::find(order.begin(), order.begin() + cut, city)
                        == order.begin() + cut)
                {
                        order[cut++] = city;
                 }
            }

            int n1 = rand() % n;
            int n2 = rand() % n;
            std::swap(order[n1], order[n2]);



            computeCost();
        }

        bool operator<(const Travel &other)
        {
            return cost < other.cost;
        }






        std::vector<int> order;
        int cost, n;
        static std::vector<std::vector<int>> distances;




};



#endif // TRAVEL_H
