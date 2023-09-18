#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
protected:
  double cost;

public:
  inline auto getCost() const {return cost;}

  inline auto operator<(const Individual &other) const
  {
    return cost < other.cost;
  }

};

#endif // INDIVIDUAL_H
