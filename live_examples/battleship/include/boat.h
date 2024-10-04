#ifndef BOAT_H
#define BOAT_H

enum class Boat
{
  Carrier,
  Cruiser,
  Destroyer,
  Minesweeper,
  Submarine,
  None
};


struct Cell
{
  Boat boat{Boat::None};
  bool hit = false;

  char print() const
  {

    if(hit)
      return 'x';

    switch(boat)
    {
      case Boat::Carrier:
        return 'A';
      case Boat::Cruiser:
        return 'C';
      case Boat::Destroyer:
        return 'D';
      case Boat::Minesweeper:
        return 'M';
      case Boat::Submarine:
        return 'S';
      case Boat::None:
        return '.';
    }
    return {};
  }


};











#endif // BOAT_H
