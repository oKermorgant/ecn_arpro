#ifndef CELL_H
#define CELL_H

struct Cell
{
  char type;
  bool visible = false;

  Cell(char _type = '.')
  {
    type = _type;
  }

  bool makeVisible()
  {
    if(visible)
      return false;

    visible = true;
    return type != '.';
  }

  char content()
  {
    if(visible)
    {
      if(type == '.')
        return 'x';
      return type;
    }
    return '.';
  }


};

#endif // CELL_H
