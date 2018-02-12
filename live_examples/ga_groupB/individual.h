#ifndef INDIVIDUAL_H

#define INDIVIDUAL_H

#include <iostream>
#include <math.h>

class Individual
{
  public:

    bool operator==(Individual other)
    {
        return x == other.x && y == other.y;
    }


    void randomize()
    {
        x = (10.*rand())/RAND_MAX - 5;
        y = (10.*rand())/RAND_MAX - 5;
        computeCost();
    }

    void computeCost()
    {
        cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
    }

    void cross(Individual i1, Individual i2)
    {
        double alpha = (1.*rand())/RAND_MAX;

        x = alpha*i1.x + (1-alpha)*i2.x;
        y = alpha*i1.y + (1-alpha)*i2.y;

        mutate();
    }

    void mutate()
    {
        double change = (.2*rand())/RAND_MAX - .1;
        x += change;

        change = (.2*rand())/RAND_MAX - .1;
        y += change;

        if(fabs(x) > 5)
            x = 5*x/fabs(x);

        if(fabs(y) > 5)
            y = 5*y/fabs(y);

        computeCost();
    }

    void print()
    {
        std::cout << "(" << x << ", " << y << ") -> " << cost << std::endl;
    }



    double x=0, y=0;
    double cost;
};

#endif
