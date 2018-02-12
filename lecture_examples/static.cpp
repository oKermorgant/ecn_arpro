#include<iostream>

using namespace std;

class MyClass
{
public:
    static double x;
    static void PrintX();
};

double MyClass::x = 0;
void MyClass::PrintX() {cout << "MyClass::x: "<< x << endl;}


namespace MyNamespace
{
    double x;
    void PrintX()  {cout << "MyNamespace::x: "<< x << endl;}
}
›
int main()
{
    MyClass::x = 1;
    MyClass::PrintX();
    MyNamespace::x = 2;
    MyNamespace::PrintX();
}