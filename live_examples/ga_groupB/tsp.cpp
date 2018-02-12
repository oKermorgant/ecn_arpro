#include <yaml-cpp/yaml.h>
#include <vector>
#include "travel.h"
#include "ga.h"
#include <chrono>

using namespace std;

std::vector<std::vector<int>> Travel::distances;

int main()
{
    YAML::Node data = YAML::LoadFile("../tsp.yaml");

    int n = data["cities"].size();

    vector<vector<int>> distances(n);
    for(int i = 0; i<n;++i)
    {
        for(int j = 0; j<n;++j)
            distances[i].push_back(data[i][j].as<int>());
    }

    Travel::distances = distances;
    Travel best_of_the_best;


    best_of_the_best.randomize();
   best_of_the_best.print(data["cities"]);

   std::chrono::time_point<std::chrono::system_clock> start, end;
   start = std::chrono::system_clock::now();


    for(int i = 0; i < 100; ++i)
    {
        Travel best;
        ga(best);
        //best.print(data["cities"]);
        if(compare(best, best_of_the_best))
            best_of_the_best = best;
    }

    best_of_the_best.print(data["cities"]);
    end = std::chrono::system_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count() << " ms" << std::endl;


    best_of_the_best.randomize();
   best_of_the_best.print(data["cities"]);


}
