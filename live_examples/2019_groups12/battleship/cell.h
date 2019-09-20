#ifndef CELL_H
#define CELL_H

struct Cell
{
  char type;
  bool visible = true;

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
      return type;
    return '.';
  }


};

#endif // CELL_H
