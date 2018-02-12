#include <iostream>
#include <map>
#include "function_indiv.h"
#include "genetic_algo.h"

using namespace std;

int main(int argc, char ** argv)
{
    std::srand(std::time(0));

    Position f;f.Randomize();

    /* config parameters :
     *
     *  int keep_best = 5;          // how many of the best individuals are always kept
     *  int iter_max = 100;         // max iterations
     *  int iter_out = 30;          // max iterations if it is always the same best individual
     *  int full_population = 500;  // population size
     */

    Config config;
    config.iter_max = 100;
    config.iter_out = 30;

    // single-run solver
    SolveGA(f, config);

    cout << "Final: ";
    f.Print();

    f.Randomize();
    cout << "Random: ";
    f.Print();

}
