#include "a_star.h"
#include "puzzle.h"

int main()
{
  // all puzzles are initialized as the goal
  Puzzle puzzle, goal;
    // so we randomize the start
    puzzle.randomize(100);

    ecn::Astar(puzzle, goal);

}
