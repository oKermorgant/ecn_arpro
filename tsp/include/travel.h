#ifndef Travel_H
#define Travel_H

#include <vector>
#include <numeric>

class Travel
{
public:
  std::vector<int> ordering;

  Travel()
  {
    // make sure ordering is all values between 0 and number of cities
    ordering.resize(n_cities);
    std::iota(ordering.begin(), ordering.end(), 0);
  }

  void randomize();

  static void registerDistances(const std::vector<std::vector<int> > &_distances)
  {
    distances = _distances;
    n_cities = distances.size();
  }

  void computeCost();
  void crossAndMutate(const Travel &t1, const Travel &_mother);

  inline double evaluate() const
  {
    return cost;
  }

protected:
  static std::vector<std::vector<int> > distances;
  static unsigned int n_cities;
  int cost;
};



#endif // Travel_H
