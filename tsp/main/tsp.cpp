#include <iostream>
#include <ga.h>
#include <travel.h>
#include <interface.h>
using namespace std;

int main()
{
  Interface interface ("tsp_2020.yaml");

  Travel::registerDistances(interface.distances);

  Travel t;
  t.randomize();
  cout << "Random solution" << endl;

  interface.print(t.ordering);
  interface.display(t.ordering);
  t = solveGA<Travel>();
  cout << "Optimized solution" << endl;

  interface.print(t.ordering);
  interface.display(t.ordering);




}
