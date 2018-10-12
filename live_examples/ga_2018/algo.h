#ifndef ALGO_H
#define ALGO_H

#include <algorithm>
#include <stdlib.h>
#include <time.h>


#include <vector>


template <class T>
void ga(T &best)
{
    const int pop_size = 500;
    const int max_iter = 100;
    const int k_best = 5;

    srand(time(0));

    std::vector<T> population(pop_size);
    std::vector<T> next_generation(pop_size);


    int iter = 0;
    while(iter < max_iter)
    {
        iter++;

        // elitism
        std::nth_element(population.begin(), population.begin()+k_best,
                         population.end());

        for(int k = 0; k < k_best; ++k)
            next_generation[k] = population[k];

        std::sort(population.begin(), population.begin()+k_best);
        best = population.front();

        // tournament
        for(int k = k_best; k < pop_size/2; ++k)
        {
            int n1 = rand() % pop_size;
            int n2 = rand() % pop_size;
            while(n1 == n2)
                n2 = rand() % pop_size;

            if(population[n1] < population[n2])
                next_generation[k] = population[n1];
            else
                next_generation[k] = population[n2];
        }

        // crossing
        for(int k = pop_size/2; k < pop_size; ++k)
        {
            int n1 = rand() % pop_size/2;
            int n2 = rand() % pop_size/2;
            while(n1 == n2)
                n2 = rand() % pop_size/2;
            next_generation[k].reset(next_generation[n1], next_generation[n2]);
            next_generation[k].mutate();
            next_generation[k].computeCost();
        }

        population = next_generation;

    }
















}


#endif // ALGO_H
