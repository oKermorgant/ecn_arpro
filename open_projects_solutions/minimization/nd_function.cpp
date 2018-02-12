#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "nd_vector.h"

using namespace std;


double rand_double(double low, double up)
{
    // random number between low and up
    return low + ((double) (rand()) / RAND_MAX)*(up-low);
}

unsigned int n = 3; // x-dimension
Vector Q(n, 0), r(n, 0);

double f(Vector x)
{
    double ret = 0;
    for(unsigned int i=0;i<n;++i)
        ret += Q[i]*x[i]*x[i] + r[i]*x[i];
    return ret;
}

Vector df(Vector x)
{
    Vector ret(n,0);
    for(unsigned int i=0;i<n;++i)
        ret[i] = 2*Q[i]*x[i] + r[i];
    return ret;
}



int main(int argc, char ** argv)
{
    Vector x(n,0);
    // randomize
    srand(clock());
    for(unsigned int i=0;i<n;++i)
    {
        x[i] = rand_double(-5, 5);
        // Q[i] must be positive so that the function x-> xˆT.Q.x + rˆT.x has a minimum
        Q[i] = rand_double(1, 10);
        r[i] = rand_double(-5, 5);
    }

    // find it with gradient descent
    double lambda = 0.1;
    double dx_min = 0.0001;
    Vector dx(n, dx_min);

    unsigned int i;

    while(dx.Norm() > dx_min)
    {
        std:: cout << "trying " << x.Print() << endl;

        dx = -lambda*df(x);
        x = x + dx;
    }

    cout << "Found minimum: f"<< x.Print() << " = "<< f(x) << endl;

    for(unsigned int i=0;i<n;++i)
        x[i] = -r[i]/(2*Q[i]);
    cout << "Theoretical minimum: f"<< x.Print() << " = " << f(x) << endl;






}
