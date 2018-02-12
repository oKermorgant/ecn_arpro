#ifndef GA_H
#define GA_H

#include <vector>
#include <algorithm>



template <class Indiv>
void ga(Indiv& best)
{
    const int n = 100;
    const int max_iter = 200;
    const int keep = 5;
    const int max_same = 40;

    std::vector<Indiv> population(n+n/2);
    for(int i = 0; i < n; ++i)
        population[i].randomize();

    std::nth_element(population.begin(),
                     population.begin() + keep,
                     population.begin() + n);
    best = *(std::min_element(population.begin(), population.begin() + keep - 1));

    int iter = 0, same = 0;

    while(iter++ < max_iter && same < max_same)
    {
        for(int i = 0; i < keep; ++i)
            population[n+i] = population[i];

        for(int i = keep; i < n/2; ++i)
        {
            int n1 = rand() % n;
            int n2 = rand() % n;
            while(n1 == n2)
                n2 = rand() % n;

            if(population[n1] < population[n2])
                population[n+i] = population[n1];
            else
                population[n+i] = population[n2];
        }
        std::swap_ranges(population.begin(), population.begin()+n/2,
                         population.begin()+n);

        for(int i = n/2; i < n; ++i)
        {
            int n1 = rand() % n/2;
            int n2 = rand() % n/2;
            while(n1 == n2)
                n2 = rand() % n/2;

            population[i].crossAndMutate(population[n1], population[n2]);
        }

        std::nth_element(population.begin(),
                         population.begin() + keep,
                         population.end());
        auto new_best =  *(std::min_element(population.begin(), population.begin() + keep - 1));
        if(new_best < best)
        {
            best = new_best;
            same = 0;
        }
        else
            same++;

    }


}



#endif // GA_H
