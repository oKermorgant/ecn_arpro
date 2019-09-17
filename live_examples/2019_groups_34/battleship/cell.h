#ifndef CELL_H
#define CELL_H

struct Cell
{
public:
  char type = '.';
  bool was_hit = false;

  Cell(char _type = '.')
  {
    type = _type;
  }

  char display(bool hide)
  {
    if(hide)
    {
      if(was_hit)
      {
        if(type == '.')
          return 'x';
        return type;
      }
      return '.';
    }



    if(was_hit)
      return 'x';
    return type;
  }

  bool alive()
  {
    if(type == '.' || was_hit)
      return false;
    return true;
  }
};


#endif // CELL_H
