#ifndef FUNCTION_INDIV_H
#define FUNCTION_INDIV_H



#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;




class Position // gives cost and comparison operator
{
public:
    // default constructor
    Position() {Randomize();}

    // comparison operator for std::sort
    friend bool operator<(const Position &_a, const Position &_b) {return _a.cost < _b.cost;}

    // randomize: a individual is (x,y) in [-5,5]
    void Randomize()
    {
        x = -5 + (10.*rand())/RAND_MAX;
        y = -5 + (10.*rand())/RAND_MAX;
        ComputeCost();
    }

    // copy from another Position
    void Copy(const Position &_other) {x=_other.x;y=_other.y;cost=_other.cost;}

    // depends on the minimized function
    void ComputeCost()
    {                
        cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
    }

    void CrossAndMutate(Position &_father, Position &_mother)
    {
        // crossing: random mean between father and mother
        double alpha = (1.*rand())/RAND_MAX;

        x = alpha*_father.x + (1-alpha)*_mother.x;
        y = alpha*_father.y + (1-alpha)*_mother.y;

        // mutation: random variation around current point
        x += -0.5 + (1.*rand())/RAND_MAX;
        y += -0.5 + (1.*rand())/RAND_MAX;
        if(fabs(x) > 5)
            x = 5*x/fabs(x);
        if(fabs(y) > 5)
            y = 5*y/fabs(y);
        ComputeCost();
    }

    void Print()
    {
        cout << "f(" << x << ", "<< y << ") = "<< cost << endl;
    }

protected:
    double x, y, cost;
};


#endif
