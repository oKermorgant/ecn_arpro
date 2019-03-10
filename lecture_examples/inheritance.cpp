#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;


class Polygon
{
public:
    // constructor with the number of sides
    Polygon(int _n) : n(_n) {}

    // get the number of sides
    int sides() {return n;}

    // non-virtual function
    string What() {return "generic polygon";}
    // virtual function
    virtual string WhatWithVirtual() {return "...generic polygon";}

protected:
    int n;  // number of sides
};


class Triangle : public Polygon // a triangle is a polygon
{
public:
    Triangle() : Polygon(3) {}  // force sides to be 3

    bool checkTriangle()
    {
      return n == 3;
    }

    // overload of non-virtual function
    string What() {return name;}
    // overload of virtual function
    string WhatWithVirtual() {return name;}
protected:
    string name = "triangle";  // number of sides
};


class Square// a square is not a polygon
{
public:
    Square()  {n=4;}  // force sides to be 4
int sides() {return n;}
    // overload of non-virtual function
    string What() {return name;}
    // overload of virtual function
    string WhatWithVirtual() {return name;}
protected:
    string name = "square";int n;  // number of sides
};

// this function gets a Polygon by value (copy)
void PassByValue(Polygon p)
{
    cout << "Pass by value" << endl;
    cout << "   I just got a " << p.What() << endl;
    cout << "   It is actually a " << p.WhatWithVirtual() << " (I hope)" << endl;
    cout << "   Anyway it has " << p.sides() << " sides" << endl << endl;
}


// this function gets a Polygon by reference (actual object, no copy)
void PassByReference(Polygon& p)
{
    cout << "Pass by reference" << endl;
    cout << "   I just got a " << p.What() << endl;
    cout << "   It is actually a " << p.WhatWithVirtual() << endl;
    cout << "   Anyway it has " << p.sides() << " sides" << endl << endl;
}


template <class T>
void passWithTemplate(T p)
{
    cout << "Pass with template" << endl;
    cout << "   I just got a " << p.What() << endl;
    cout << "   It is actually a " << p.WhatWithVirtual() << endl;
    cout << "   Anyway it has " << p.sides() << " sides" << endl << endl;

}



int main()
{
    Polygon p(5);
    Triangle t; // no need to give the sides, it is a triangle...
    Square s;

    cout << p.sides() << endl;

    // the correct function (virtual or not) will be called if directly called from the object
    cout << "p is a " << p.What() << endl;
    cout << "t is a " << t.What() << endl;
    cout << "s is a " << s.WhatWithVirtual() << endl;
    cout << endl;

    passWithTemplate(p);
    passWithTemplate(t);
    passWithTemplate(s);
   // passWithTemplate(1);
   // passWithTemplate(std::vector<double>(3,4));

    PassByValue(p);
    PassByValue(t);
  //  PassByValue(s);

    PassByReference(p);
    PassByReference(t);
    //PassByReference(s);


    // what about storing polygons in a vector?
    // a vector of values does not keep track of the actual class
    /*std::vector<Polygon> vec = {p, t, s};
    cout << "exploring vector of values" << endl;
    for(auto &elem: vec)
    {
        cout << "this element is a " << elem.What() << endl;
        cout << "this element is actually a " << elem.WhatWithVirtual() << endl;
    }

    // to keep track we need a vector of references (pointers)
    std::vector<Polygon*> vec_ref = {&p, &t, &s};
    cout << '\n' << "exploring vector of pointers" << endl;
    for(auto &elem: vec_ref)
    {
        // functions then have to be called with arrow instead of dot
        // still does not work if function is not virtual
        cout << "this element is a " << elem->What() << endl;
        cout << "this element is actually a " << elem->WhatWithVirtual() << endl;
    }*/

}
