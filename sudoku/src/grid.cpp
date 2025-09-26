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

  std::cout << "Solved in "
            << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
            << " \u03BCs" << std::endl;

  print();

  if(result && std::all_of(cells.begin(), cells.end(), Cell::isValid))
    std::cout << "Sudoku was solved with "
              << guesses << " wild guesses, "
                            "had to cancel and go back " << cancels << " times" << std::endl;
  else
  {
    std::cout << "Grid is not valid" << std::endl;
  }
}


// TODO section


/// Returns True if c1 is considered a better next cell to investigate
/// than c2, False otherwise
/// improve the current version by taking into account the number of candidates
/// for now just picks any empty cell
bool bestNextCell(const Cell &c1, const Cell &c2)
{
  return c1.digit() < c2.digit();
}

/// main backtracking function
bool Grid::solveNextCell()
{

  // TODO check if the grid is already full
  if(std::all_of(cells.begin(), cells.end(), Cell::isAssigned))
    return true;

  // identify next cell to go, it is just the best under whatever bestNextCell considers
  auto &next_cell{*std::min_element(cells.begin(), cells.end(), bestNextCell)};

  // just a check, it is meaningless to continue with an already solved cell
  if(next_cell.digit())
    throw std::runtime_error("Next cell already has a digit");

  // TODO implement backtracking algorithm candidate loop
  // you may place all printing code inside if(display) blocks
  for(auto guess: next_cell.candidates())
  {
    //print(&next_cell);  // to display the picked guess
  //print(&next_cell, true);  // to display this guess was reset
  }
  return false;
}
