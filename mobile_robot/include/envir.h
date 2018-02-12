#ifndef ENVIR_H
#define ENVIR_H

#include <vector>
#include <geom.h>

namespace arpro
{


class Robot;

struct Environment
{
    std::vector<Pose> walls;
    Pose target;
    std::vector<double> x_hist, y_hist;
    std::vector<Robot*> robots_;

    unsigned int iter;

    Environment();

    // the target draws a cardoid curve
    void updateTarget();

    void addRobot(Robot &_robot);

    void plotTrajectory(std::string name_, std::vector<double> x_, std::vector<double> y_, std::string color_);

    // plots the trajectory in the given environment
    void plot();
};

}

#endif // ENVIR_H
