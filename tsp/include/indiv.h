#ifndef INDIV_H
#define INDIV_H

#include <vector>

// this class just shows the needed interface for individuals used by GA.

class Indiv
{
public:
    // Constructor may also initialize this individual and compute its cost
    Indiv() {}

    // Compute and store the individual's cost in the cost member variable
    void computeCost();

    // Modify this from the crossing from 2 parents followed by a mutation
    void crossAndMutate(Indiv &_p1, Indiv &_p2);


    double cost;

    // static functions useful when cost is computed in parallel

    // Inits the population vector at a given size.
    // For cases where the individual is initialized in its constructor,
    // resizing the population vector is enough.
    // Cost should be computed before returning
    static void initPopulation(std::vector<Indiv>& population, int size);

    // Ensures that all costs have been computed
    static void waitForCosts() {}


};

#endif // INDIV_H
