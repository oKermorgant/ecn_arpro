#include <random>
#include <chrono>
#include <iostream>

#include "rastrigin.h"
#include "genetic_algo.h"


void XY::randomize()
{
  // TODO random coord between -5 and 5
  x = rand(-5, 5);
  y = rand(-5, 5);

  computeCost();
}

void XY::cross(const XY &p1, const XY &p2)
{
  const auto t{rand(0.05,0.95)};
  x = p1.x + t*(p2.x-p1.x);
  y = p1.y + t*(p2.y-p1.y);

}

void XY::mutate()
{
  x += 0.5*rand(-1,1);
  y += 0.5*rand(-1,1);
  sat(x);
  sat(y);

  computeCost();
}

void XY::computeCost()
{
  cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
}

double XY::rand(double min, double max)
{
  return min + (max-min)*rand01(engine);
}

void XY::print() const
{
  std::cout << "(" << x << ", " << y << ") : "
            << cost << std::endl;
}

void XY::sat(double &coord)
{
  if(coord < -5)
    coord = -5;
  else if(coord > 5)
    coord = 5;
}

std::default_random_engine XY::engine;
std::uniform_real_distribution<> XY::rand01;


int main()
{
  XY best;

  const auto start{std::chrono::steady_clock::now()};

  geneticAlgo(best);

  const auto end{std::chrono::steady_clock::now()};

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
            << " ms\n";

  best.print();


  const auto v{std::vector{1,5,4,3,3,6,2,8,2,0}};

  auto print = [](std::vector<int> v)
  {
    for(auto &elem: v)  std::cout << elem << " ";
    std::cout << std::endl;
  };

  auto u{v};
  std::sort(u.begin(), u.end());
  print(u);

  u = v;
  std::partial_sort(u.begin(), u.begin()+3, u.end());
  print(u);

  u = v;
  std::sort(u.begin(), u.begin()+3);
  print(u);

  u = v;
  std::nth_element(u.begin(), u.begin()+3, u.end());
  print(u);


}
