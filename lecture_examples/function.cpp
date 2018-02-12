#include <iostream>

using namespace std;


namespace ecn
{
    int f(int x)
    {
     cout << "Calling f int from ecn namespace" << endl;
        return x - 1;
    }
}




int f(int x)
{
    cout << "Calling f int" << endl;
    x = x+ 1;

    return x;
}

double f(double x)
{
    cout << "Calling f double" << endl;
    x = x+ 1;
    return x;
}




int main()
{
    f(4);
    f(3.14);
    ecn::f(4);

}
