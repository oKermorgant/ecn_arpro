#include <yaml-cpp/yaml.h>
#include <vector>
#include "travel.h"
#include "ga.h"
#include <chrono>


using std::vector;

vector<vector<int>> Travel::distances;

int main()
{
    srand(clock());
    YAML::Node data = YAML::LoadFile("../tsp.yaml");

    const int n = data["cities"].size();
    Travel::distances.resize(n);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
            Travel::distances[i].push_back(data[i][j].as<int>());
    }


    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Travel best;
    best.randomize();
    for(int i = 0; i < 100; ++i)
    {
        Travel t;
        ga(t);
        if(t < best)
            best = t;
    }
    best.print(data["cities"]);
    end = std::chrono::system_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count() << " ms" << std::endl;




}
