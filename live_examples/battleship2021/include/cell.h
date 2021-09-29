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
  char display() const
  {
    switch (boat)
    {
    case Boat::AIRCRAFT: return 'A';
    case Boat::MINESWEEPER: return 'M';
    case Boat::SUBMARINE: return 'S';
    case Boat::DESTROYER: return 'D';
    case Boat::CRUISER: return 'C';
    case Boat::NONE: return '.';
    }
    return {};
  }

  Boat boat = Boat::NONE;
  bool hit{false};
};

inline std::ostream & operator<<(std::ostream &os, const Cell &cell)
{
  //os ;
  return  os<< cell.display();
}


#endif // CELL_H
