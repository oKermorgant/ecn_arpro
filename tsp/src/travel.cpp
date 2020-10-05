#include <travel.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <rand_util.h>

using namespace std;

// static variables
std::vector<std::vector<int> > Travel::distances = {};
uint Travel::n_cities = 0;


void Travel::randomize()
{
  // random shuffle of the ordering


  computeCost();
}

void Travel::computeCost()
{
  cost = 0;
}

void Travel::crossAndMutate(const Travel &t1, const Travel &t2)
{
  // update this travel from a crossing between t1 and t2


  // mutate this travel


  // compute cost
  computeCost();
}

