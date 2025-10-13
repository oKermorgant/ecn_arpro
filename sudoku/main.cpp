#include <sudoku/grid.h>

int main(int argc, char** argv)
{

  auto sum = add(1,2);

  // load the starting grid from file as a std::array
  // "easy" is the name of the starting grid (see starts folder)
  const auto starting_grid{getStart(argc, argv, "hard")};

  // initialize an actual grid from this
  Grid grid(starting_grid);

  // check any argument on display each step
  grid.display = useDisplay(argc, argv, false);

  // solve it
  grid.solve();

  grid.print();


}
