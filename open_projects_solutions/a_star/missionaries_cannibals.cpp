#include "a_star.h"
#include <iostream>
#include "missionaries_cannibals.h"


int main()
{
    // start with missionaries and cannibals on the left side
    MissionariesCannibals start(3, 3), goal;
    start.boatSize(2);

    ecn::Astar(start, goal);

}
