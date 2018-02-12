#ifndef GALG_H
#define GALG_H

#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <algorithm>

struct Config
{
    int keep_best = 5;
    int iter_max = 100;
    int iter_out = 30;
    int full_population = 500;
};

inline unsigned int rand_int(const unsigned int &_start, const unsigned int &_length)
{
    return rand()%_length+_start;
}

// perform a single run with a random population
template<class T> T SolveGA(T &best, const Config config = Config())
{
    const int half_population = config.full_population/2;

    // init first population from random individuals
    std::vector<T> population(config.full_population + half_population);

    // finds n-best elements and put them at the front of the vector
    std::nth_element(population.begin(), population.begin()+config.keep_best, population.begin()+config.full_population);
    best.Copy(population[0]);

    // loop until exit conditions
    unsigned int i, iter=0,iter_follow=0;
    unsigned int n1,n2;
    while(iter++ < config.iter_max && iter_follow< config.iter_out)   // max iteration and max iteration where the best is always the same
    {
        // we keep the best individuals anyway
        for(i=0;i<config.keep_best;++i)
            population[config.full_population+i].Copy(population[i]);

        // selection, 1 vs 1 tournament to fill half of the population
        for(i=config.keep_best;i<half_population;++i)
        {
            n1 = rand_int(0,config.full_population);
            n2 = rand_int(0,config.full_population);
            while(n1 == n2)
                n2 = rand_int(0,config.full_population);
            if(population[n1] < population[n2])
                population[config.full_population+i].Copy(population[n1]);
            else
                population[config.full_population+i].Copy(population[n2]);
        }

        // here population is [old population ... half of new population]

        // put new population at the beginning
        for(i=0;i<half_population;++i)
            population[i].Copy(population[config.full_population+i]);

        // crossing and mutation to fill other half of the new population
        for(i=half_population;i<config.full_population;++i)
        {
            n1 = rand_int(0,half_population);
            n2 = rand_int(0,half_population);
            while(n1 == n2)
                n2 = rand_int(0,half_population);
            //   std::cout << "  new " << i << " is crossing between " << n1 << " and " << n2 << std::endl;
            // cross between parents + compute cost
            population[i].CrossAndMutate(population[n1],population[n2]);
        }

        // update costs
        std::nth_element(population.begin(), population.begin()+config.keep_best, population.begin()+config.full_population);

        // check for best individual
        if(population[0] < best)
        {
            // found new best individual
            // reset counter
            iter_follow = 0;
            // update best
            best.Copy(population[0]);
            std::cout << "   new best element!" << std::endl;
        }
        else
            iter_follow += 1;   // always the same winner

        // prints update
        std::cout << "Generation " << iter << ", best element has been best for " << iter_follow << " generations" << std::endl;
    }
    return best;
}


#endif // GALG_H
