#include "individual.h"
#include "ga.h"

int main()
{
    srand(clock());

    Individual best_of_the_best;
    best_of_the_best.randomize();
     best_of_the_best.print();

    for(int i = 0; i < 100; ++i)
    {
        Individual best;
        ga(best);

        if(compare(best, best_of_the_best))
            best_of_the_best = best;

    }


    best_of_the_best.print();


}
