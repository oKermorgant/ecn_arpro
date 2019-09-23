#include <iostream>

const double a = 3;
const double b = 235;
const double c = -100;

double f(double x)
{
  return a*x*x + b*x + c;
}

double f_prime(double x)
{
  return 2*a*x + b;
}

int main()
{
  const auto xmin = -b/(2*a);


  // initialize things
  double x = 0;
  uint max_iter = 1000;
  const double gain = 0.05;
  const double gradient_min = 0.001;

  uint iter(0);
  double gradient(2*gradient_min);

  while(iter < max_iter && std::abs(gradient) > gradient_min)
  {

    // update x somehow
    gradient = f_prime(x);
    x -= gain * gradient;

    iter++;

    std::cout << "Current guess: " << f(x) << " at x = " << x << std::endl;

  }


  if(iter != max_iter)
  {
  std::cout << "Found minimun " << f(x)
            << " at x = " << x
            << " in " << iter
            << " iterations" << std::endl;
  }
  else
    std::cout << "Could not find minimum\n";
std::cout << "Theoretical minimun: " << f(xmin) << " at x = " << xmin << std::endl;

}

















