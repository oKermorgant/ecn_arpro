#include <iostream>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

double a, b, c;

double rand_double(double low, double up)
{
    // random number between low and up
    return low + ((double) (rand()) / RAND_MAX)*(up-low);
}


double f(double x)
{
    return a*x*x + b*x + c;
}

double df(double x)
{
    return 2*a*x + b;
}



int main(int argc, char ** argv)
{
    srand(clock());
    // randomize a, b and c
    // a must be positive so that the function x-> a*xˆ2 + b*x + c has a minimum
    a = rand_double(1, 10);
    b = rand_double(-5, 5);
    c = rand_double(-5, 5);

    double x = 0;
    // starting position from arguments if any
    if(argc == 2)
        x = atof(argv[1]);

    // find it with gradient descent
    double lambda = 0.1;
    double dx_min = 0.00001;
    double dx = 2*dx_min;
    while(abs(dx) > dx_min)
    {
        std:: cout << "trying "<< x << "..."<< endl;
        dx = df(x);
        x -= lambda*dx;
    }
    cout << "Using a="<< a << ", b="<< b << ", c="<< c << endl;
    cout << "Found minimum: f("<< x << ") = "<< f(x) << endl;
    cout << "Theoretical minimum: f(" << -b/(2*a) << ") = " << f(-b/(2*a)) << endl;

}
