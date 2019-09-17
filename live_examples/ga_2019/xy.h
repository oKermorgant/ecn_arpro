#ifndef XY_H
#define XY_H


class XY
{
public:
  XY();
  void randomize();
  void mutate();

  void cross(const XY &p1, const XY &p2);
  void print() const;

  double cost() const
  {
    return cost_;
  }


private:
  double x_, y_, cost_;

  void computeCost();

  static double rand_range(double min, double max);
};

#endif // XY_H
