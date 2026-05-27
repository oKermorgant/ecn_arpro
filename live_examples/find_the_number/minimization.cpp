#include <iostream>
#include <vector>

const double a{3.};
const double b{2};
const double gmax{1e-3};
const auto itermax{100};

auto fprime(double x)
{
  return 2*a*x+b;
}


void update(double & x, double fprime)
{
  const auto lambda{0.1};
  x -= lambda*fprime;
}




int main()
{
  int x[4]{0,1,2,3};
  std::vector<int> v{0,1,2,3};

  auto xc = x;
  xc[0] = 4;

  auto vc = v;
  vc[0] = 4;






}
  /*



  double x = 0.;

  auto iter{0};
  while(iter++ < itermax)
  {
    const auto g{fprime(x)};

    if(std::abs(g) < gmax)
      break;

    update(x, g);
  }

  std::cout << "Found @ " << x
            << " vs " << -b/(2*a) << std::endl;


}
*/
