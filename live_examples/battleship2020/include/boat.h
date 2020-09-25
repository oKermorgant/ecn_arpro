#ifndef BOAT_H
#define BOAT_H

#include <vector>


enum class BoatType
{
  NONE,
  AIRCRAFT,
  DESTROYER,
  SUBMARINE,
  CRUISER
};


struct Boat
{
  BoatType type = BoatType::NONE;
  bool hit = false;

  char display(bool hide = false) const
  {
    const char letter_hit{'X'};

    if(hide)
    {
      if(hit)
      {
        if(type == BoatType::NONE)
          return letter_hit;
        return letter(type);
      }
      else
        return letter(BoatType::NONE);
    }

    if(hit)
      return letter_hit;
    return letter(type);
  }

  static std::vector<std::pair<BoatType, int>> allBoats()
  {
    return {
        {BoatType::AIRCRAFT, 5},
        {BoatType::DESTROYER, 3},
        {BoatType::SUBMARINE, 2},
        {BoatType::CRUISER, 4}
      };
  }

private:
  static char letter(BoatType type)
  {
    switch(type)
    {
    case BoatType::AIRCRAFT:
      return 'A';
    case BoatType::SUBMARINE:
      return 'S';
    case BoatType::DESTROYER:
      return 'D';
    case BoatType::CRUISER:
      return 'C';
    default:
      return '.';
    }
  }
};

#endif // BOAT_H
