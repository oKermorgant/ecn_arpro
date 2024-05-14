#include <sudoku/grid.h>
#include <iostream>
#include <chrono>

Grid::Grid(const StartingGrid& starting_grid)
{
  /// initialize cells from starting grid
  /// empty cells are initialized with all candidates [1..9] at this point
  uint row = 0;
  for(const auto &line: starting_grid)
  {
    uint col = 0;
    for(const auto &elem: line)
    {
      cells[9*row + col].init(row, col, cells, elem);
      col++;
    }
    row++;
  }

  /// TODO erase candidates according to starting grid
  /// all non-empty cells should delete their value from their neighboors' candidates

}

void Grid::solve()
{
  using Clock = std::chrono::high_resolution_clock;
  const auto start{Clock::now()};
  const auto result{solveNextCell()};
  const auto end{Clock::now()};

  print();

  std::cout << "Solved in "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " \u03BCs\n";

  if(result && std::all_of(cells.begin(), cells.end(), Cell::isValid))
    std::cout << "Sudoku was solved with "
              << guesses << " wild guesses, "
                            "had to cancel and go back " << cancels << " times" << std::endl;
  else
    std::cout << "Grid is not valid" << std::endl;
}

void Grid::print() const
{
  constexpr auto line{" -----------"};

  std::cout << line << '\n';

  auto cell{cells.begin()};
  for(auto row = 0; row < 9; ++row)
  {
    std::cout << ' ';
    for(auto col = 0; col < 9; ++col)
    {
      std::cout << (cell++)->symbol();
      if(col == 2 || col == 5)
        std::cout << '|';
      else if(col == 8)
        std::cout << '\n';
    }
    if(row == 2 || row == 5 || row == 8)
      std::cout << line << '\n';
  }
  std::cout << std::endl;
}


// TODO section


/// Returns True if c1 is considered a better next cell to investigate
/// than c2, False otherwise
/// improve the current version by taking into account the number of candidates
bool bestNextCell(const Cell &c1, const Cell &c2)
{
  return c1.digit() < c2.digit();
}


/// main backtracking function
bool Grid::solveNextCell()
{
  // TODO check if the grid is already full


  // identify next cell to go, it is just the best under whatever bestNextCell considers
  auto &next_cell{*std::min_element(cells.begin(), cells.end(), bestNextCell)};

  // just a check, it is meaningless to continue with an already solved cell
  if(next_cell.digit())
    throw std::runtime_error("Next cell already has a digit");

  // TODO implement backtracking algorithm candidate loop
  // you may place all printing code inside if(display) blocks






  return false;
}
