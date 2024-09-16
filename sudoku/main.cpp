#include <sudoku/grid.h>
#include <iostream>


int main(int argc, char** argv)
{
  // load the starting grid from file as a std::array
  // "easy" is the name of the starting grid (see starts folder)
  const auto starting_grid{getStart(argc, argv, "basic2")};

  // initialize an actual grid from this
  Grid grid(starting_grid);

  // check any argument on display each step
  grid.display = useDisplay(argc, argv, true);

  // solve it
  grid.solve();
}
