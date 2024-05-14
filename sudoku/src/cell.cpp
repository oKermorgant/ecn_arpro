#include <sudoku/cell.h>
#include <sudoku/grid.h>
#include <iostream>

void Cell::init(uint row, uint col, std::array<Cell, 81> &grid, uint digit)
{
  if(digit)
  {
    this->digit_ = digit;
    // no candidates, we know this one
  }
  else
  {
    candidates_.resize(9);
    std::iota(candidates_.begin(), candidates_.end(), 1);
  }

  const auto cellPtr = [&grid](uint row, uint col) -> Cell*
  {return grid.data() + 9*row + col;};

  // register neighboors
  const uint quad_row = 3*(row/3);
  const uint quad_col = 3*(col/3);
  auto nb{neighboors_.begin()};
  for(uint ax = 0; ax < 9; ++ax)
  {
    // same colum, different row
    if(ax != row)
      *(nb++) = cellPtr(ax,col);
    // same row, different column
    if(ax != col)
      *(nb++) = cellPtr(row, ax);
    // same 3x3 sub-square
    const uint r = quad_row + ax / 3;
    const uint c = quad_col + ax % 3;
    if(r != row && c != col)
      *(nb++) = cellPtr(r, c);
  }
}


// TODO section

void Cell::prune(uint guess)
{

}

void Cell::restore(uint guess)
{

}


void Cell::set(uint guess)
{

}

void Cell::cancel()
{

}
