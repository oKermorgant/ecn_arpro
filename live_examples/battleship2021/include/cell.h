#ifndef CELL_H
#define CELL_H

#include <ostream>

enum class Boat
{
  AIRCRAFT,
  MINESWEEPER,
  DESTROYER,
  CRUISER,
  SUBMARINE,
  NONE
};



struct Cell
{
  bool isAlive() const
  {
    return boat != Boat::NONE && !hit;
  }

  char display() const
  {
    if(boat == Boat::NONE)
    {
      return hit ? 'X' : '.';
    }

    if(!hit)
      return '.';

    switch (boat)
    {
    case Boat::AIRCRAFT: return 'A';
    case Boat::MINESWEEPER: return 'M';
    case Boat::SUBMARINE: return 'S';
    case Boat::DESTROYER: return 'D';
    case Boat::CRUISER: return 'C';
    default: return '.';
    }
  }

  Boat boat = Boat::NONE;
  bool hit{false};
};

inline std::ostream & operator<<(std::ostream &os, const Cell &cell)
{
  return  os<< cell.display();
}


#endif // CELL_H
