#include <iostream>
#include <vector>
#include <string>

class Vector : public std::vector<double>
{
  public:
    Vector(int n=0) : vector<double>(n, 0) {}

    double norm()
    {
        double ret = 0;
        for(auto v: *this)
            ret += v*v;
        return ret;
      }

    void print(std::string legend)
    {
     std::cout << legend << ": (";
     for(int i=0;i<size()-1; ++i)
         std::cout << at(i) << ", ";
     std::cout << back();
     std::cout << ")" << std::endl;
    }

    Vector operator*(Vector x2)
    {
        for(int i = 0; i<size();++i)
            x2[i] *= at(i);
        return x2;
    }
};


Vector operator*(double l, Vector x)
{
    for(auto &v: x)
        v *= l;
    return x;
}




Vector operator+(Vector x1, Vector x2)
{
    for(int i = 0; i<x1.size();++i)
        x1[i] += x2[i];
    return x1;
}
Vector operator-(Vector x1, Vector x2)
{
    for(int i = 0; i<x1.size();++i)
        x1[i] -= x2[i];
    return x1;
}



int n = 3;

Vector fPrime(Vector x, Vector Q, Vector r)
{
    return 2*Q*x + r;
}


int main()
{

    srand (clock());

    Vector Q(n);
    for(int i = 0; i<n; ++i)
        Q[i] = 2 + rand() % 10;

    Vector r(n);
    for(auto &val: r)
        val =  rand() % 11 - 5 + .5;

    Vector x(n);

    double lambda = .01;
    double grad_min = 0.0001;
    double grad = 2*grad_min;
    Vector df;
    int iter_max = 10000;
    int iter = 0;

    while(iter < iter_max && grad > grad_min)
    {
        iter++;

        // compute gradient
        df = fPrime(x, Q, r);

        grad = df.norm();

        x = x -lambda * df;
    }
    if(iter == iter_max)
        std::cout << "Max iter reached\n";

    x.print("found minimum");

    for(int i = 0; i<n; ++i)
        x[i] = -r[i]/(2*Q[i]);
x.print("theoretical minimum");





}
