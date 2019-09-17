#ifndef CELL_H
#define CELL_H

struct Cell
{
public:
  Cell(char _type = '.') : type(_type) {}


  bool isEmpty() const
  {
    return type == '.';
  }

  bool isAlive() const
  {
    if(type == '.' || was_hit)
      return false;
    return true;
  }

  char display(bool human = false) const
  {
    if(human)
    {
      if(was_hit)
        return 'x';
      return type;
    }

    if(was_hit)
    {
      if(type == '.')
        return 'x';
      return type;
    }
    return '.';
  }

  char type = '.';
  bool was_hit = false;
};

#endif // CELL_H
