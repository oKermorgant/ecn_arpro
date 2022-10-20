#include "a_star.h"
#include <iostream>
#include "puzzle.h"


int main()
{
  // all puzzles are initialized as the goal
  Puzzle puzzle, goal;
    // so we randomize the start
    puzzle.randomize(70);

    ecn::Astar(puzzle, goal);

}
