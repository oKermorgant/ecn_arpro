#include <iostream>

using namespace std;

class C
{
public:
    virtual bool check() = 0;
};


class DC : public C
{
public:
    virtual bool check() {return true;}
};


class Router
{
public:
    virtual void rout() =0;
};

class ConRout : public Router
{
  public:
    //virtual void rout() {}
    virtual void addC(C& c) {cout << "addC(C) \n";}
    virtual void addC(DC& dc) {cout << "addC(DC)\n";}
};

class MyRout : public ConRout
{
  public:
    void addC(C& c) {ConRout::addC(c);}
    void addC(DC& dc) {cout << "override addC(DC)\n";}
    void rout() {}
};



int main()
{
    DC dc;
    DC dc2;
    C* c = &dc2;

    MyRout mr;
    mr.addC(*c);
    mr.addC(dc);
}
