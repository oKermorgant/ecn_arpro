#ifndef GA_H
#define GA_H

#include <vector>
#include <algorithm>
#include <iostream>


template <class Individual>
bool compare(Individual i1, Individual i2)
{
    return i1.cost < i2.cost;
}

template <class Individual>
void ga(Individual &best)
{
    // configuration
    const int n = 200;
    const int iter_max = 100;
    const int keep = 10;
    const int same_max = 30;

    // random initial population
    std::vector<Individual> population(n);

    for(auto &individual: population)
        individual.randomize();

    std::sort(population.begin(), population.end(), compare<Individual>);
    best = population[0];

    int iter = 0;
    int same = 0;
    while(iter++ < iter_max)
    {
       // init new population with 5 best
        std::vector<Individual> new_population;
        for(int i = 0; i < keep; ++i)
            new_population.push_back(population[i]);

        // tournament
        for(int i = keep; i < n/2; ++i)
        {
            int n1 = rand() % n;
            int n2 = rand() % n;
            while(n1 == n2)
                n2 = rand() % n;
            if(compare(population[n1], population[n2]))
                new_population.push_back(population[n1]);
            else
                new_population.push_back(population[n2]);
        }

        for(int i = 0; i < n/2; ++i)
        {
            int n1 = rand() % n/2;
            int n2 = rand() % n/2;
            while(n1 == n2)
                n2 = rand() % n/2;

            Individual indiv;
            indiv.cross(new_population[n1], new_population[n2]);
            new_population.push_back(indiv);
        }

        population = new_population;
        std::sort(population.begin(), population.end(), compare<Individual>);

        if(best == population[0])
        {
            same++;
            if(same == same_max)
                break;
        }
        else
        {
            same = 0;
            best = population[0];
        }
    }

   /* if(same == same_max)
        std::cout << "Finished because of always same best" << std::endl;
    else
        std::cout << "Finished because of max iterations" << std::endl;*/
}


#endif
