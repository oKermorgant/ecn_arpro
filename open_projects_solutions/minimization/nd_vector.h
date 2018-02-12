#ifndef ND_VECTOR_H
#define ND_VECTOR_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

// a simple n-dim vector

class Vector: public std::vector<double>
{
public:
    Vector(int n, double v = 0) : std::vector<double>(n, v) {}

    double Norm()
    {
        double ret = 0;
        for(unsigned int i=0;i<size();++i)
            ret += std::abs(at(i));
        return ret;
    }

    Vector operator+(const Vector v) const
    {
        Vector ret(size(),0);

        for (int i = 0; i < size(); i++)
            ret[i] = at(i) + v[i];
        return ret;
    }

    Vector& operator=(const Vector v)
    {
        for (int i = 0; i < size(); i++)
            at(i) = v[i];
        return *this;
    }

    Vector operator*(const double l) const
    {
        Vector ret(size());

        for (int i = 0; i < size(); i++)
            ret[i] = at(i)*l;
        return ret;
    }

    std::string Print()
    {
        std::stringstream ss;
        ss << "(";
        unsigned int i;
        for(i=0;i<size()-1;++i)
            ss << at(i) << ", ";
        ss << at(i) << ")";
        return ss.str();
    }
};

// gives access to double * Vector
Vector operator*(double l, Vector v)
{
    return v*l;
}

#endif // ND_VECTOR_H
