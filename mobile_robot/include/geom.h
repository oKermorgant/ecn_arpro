#ifndef GEOM_H
#define GEOM_H

#include <math.h>
#include <iostream>

// header file for basic geometry transforms


namespace arpro
{

struct Pose
{
    double x = 0;
    double y = 0;
    double theta = 0;
    Pose() {}
    Pose(double _x, double _y, double _theta=0) : x(_x), y(_y), theta(_theta) {}
    Pose transformDirect(Pose _transform) const
    {
        const double c = cos(_transform.theta);
        const double s = sin(_transform.theta);
        return Pose(_transform.x + x*c - y*s,
                    _transform.y + x*s + y*c,
                    _transform.theta + theta);
    }

    Pose transformInverse(Pose _transform) const
    {
        const double c = cos(_transform.theta);
        const double s = sin(_transform.theta);

        return Pose(x*c + y*s - c*_transform.x - s*_transform.y,
                   -x*s + y*c + s*_transform.x - c*_transform.y,
                    theta - _transform.theta);
    }
};


struct Twist
{
    double vx = 0, vy = 0, w = 0;
    Twist() {}
    Twist(double _vx, double _vy, double _w=0) : vx(_vx), vy(_vy), w(_w) {}

    Twist transformDirect(Pose _transform)
    {
        const double c = cos(_transform.theta);
        const double s = sin(_transform.theta);
        return Twist(vx*c-vy*s+_transform.y*w, vx*s+vy*c-_transform.x*w, w);
    } const

    Twist transformInverse(Pose _transform)
    {
        const double c = cos(_transform.theta);
        const double s = sin(_transform.theta);
        return Twist((vx-_transform.y*w)*c+(vy+_transform.x*w)*s,
                     -(vx-_transform.y*w)*s+(vy+_transform.x*w)*c,w);
    } const

    Twist operator+(const Twist &_other)
    {
        return Twist(vx+_other.vx, vy+_other.vy,w+_other.w);
    }
    friend std::ostream& operator<<(std::ostream& os, const Twist &_twist)
    {
        os << "(" << _twist.vx << ", " << _twist.vy << ", " << _twist.w << ")";
        return os;
    }
};




}




#endif // GEOM_H
