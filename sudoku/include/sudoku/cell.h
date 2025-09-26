#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <algorithm>
#include <vector>
#include <array>

class Grid;

class Cell
{
  // how many times a given number was pruned, size 10 to forget about index 0
  std::array<uint, 10> pruned_count_{};

  // current guess
  uint digit_ = 0;

  // candidates
  std::vector<uint> candidates_;

  // Cells that cannot have the same digit as this one
  std::array<Cell*, 8+8+8-4> neighboors_;

  /// TODO Restore the guess as a candidate for this cell if it was part of the candidates
  /// unless it was pruned several times
  void restore(uint guess);

  /// TODO Remove this guess from the candidates and increments how many times this guess was pruned
  void prune(uint guess);

public:

  Cell() {}

  // we cannot copy a Cell (would mess up the pointers)
  Cell(const Cell &src) = delete;

  void init(uint row, uint col, std::array<Cell, 81> &grid, uint digit = 0);

  /// Returns the symbol this cell should be printed as
  inline char symbol() const
  {
    return digit_ ? digit_+48 : ' ';
  }

  /// Some accessors
  inline auto candidates() const {return candidates_;}
  inline auto neighboors() const {return neighboors_;}
  inline auto digit() const
  {
    return digit_;
  }
  inline auto pruned() const
  {
    std::vector<int> pruned;
    for(int i = 0; i < pruned_count_.size(); ++i)
    {
      if(pruned_count_[i])
        pruned.push_back(i);
    }
    return pruned;
  }

  /// simply deletes the guess from our candidates if it is here
  inline void eraseCandidate(uint guess)
  {
    if(auto elem{std::find(candidates_.begin(), candidates_.end(), guess)};
        elem != candidates_.end())
      candidates_.erase(elem);
  }

  /// TODO Set the guess for this cell and prunes it from its neighboors
  void set(uint guess);

  /// TODO Cancels the last guess that was done on this cell
  /// Restore the guess on its neighboors if it was pruned
  void cancel();

  inline bool operator==(uint guess) const
  {
    return digit_ == guess;
  }

  // static functions to use in algorithms

  /// returns True if this cell has an assigned digit
  /// (guess or given from the start)
  inline static bool isAssigned(const Cell &cell)
  {
    return cell.digit_ != 0;
  }

  /// returns True if this cell is valid: has a digit different from its neighboors
  inline static bool isValid(const Cell &cell)
  {
    if(cell.digit_ == 0)
      return false;
    return std::all_of(cell.neighboors_.begin(), cell.neighboors_.end(),
                       [&cell](const auto &nb){return cell.digit_ != nb->digit_;});
  }
};

#endif
