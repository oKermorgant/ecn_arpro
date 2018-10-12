#include "xy.h"
#include <stdlib.h>
#include <math.h>

XY::XY(int min, double max)
{
    x = ((max-min)*rand())/RAND_MAX + min;
    y = ((max-min)*rand())/RAND_MAX  + min;
    computeCost();
}

void XY::computeCost()
{
    int x;
    this->x;


cost = 20 + x*x + y*y - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));

}


void XY::reset(const XY& p1, const XY& p2)
{
double a = (1.*rand())/RAND_MAX;
x = a*p1.x + (1-a)*p2.x;
y = a*p1.y + (1-a)*p2.y;

}

void XY::mutate()
{
    x += (0.2*rand())/RAND_MAX;
    y += (0.2*rand())/RAND_MAX;
    if(fabs(x) > 5)
        x = x/fabs(x)*5;
    if(fabs(y) > 5)
        y = y/fabs(y)*5;
}

