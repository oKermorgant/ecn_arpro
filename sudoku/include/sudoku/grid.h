#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#include <sudoku/starting_grids.h>
#include <sudoku/cell.h>
#include <array>

class Grid
{
public:
  bool display = false;
  explicit Grid(const StartingGrid &starting_grid);

  void solve();

  void print() const;

private:

  bool solveNextCell();
  std::array<Cell, 81> cells;
  uint guesses{};
  uint cancels{};
};

#endif
