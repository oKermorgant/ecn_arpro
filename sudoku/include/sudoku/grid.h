#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#include <sudoku/starting_grids.h>
#include <sudoku/cell.h>
#include <array>

class Grid
{
  using Cells = std::array<Cell, 81>;
public:
  bool display = false;
  explicit Grid(const StartingGrid &starting_grid);

  void solve();

  void print() const;
  void print(Cells::const_iterator candidate, bool canceled = false) const;

private:

  bool solveNextCell();
  Cells cells;
  uint guesses{};
  uint cancels{};
};

#endif
