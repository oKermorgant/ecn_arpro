#include <vector>
#include <math.h>
#include <matplotlibcpp.h>
#include <sstream>
#include <algorithm>
#include <robot.h>
#include <envir.h>


namespace arpro
{

    Environment::Environment()
    {
        iter=0;
        x_hist.clear();
        y_hist.clear();

        walls.resize(4);
        walls[0].x = walls[1].x = walls[1].y = walls[2].y = -10;
        walls[2].x = walls[3].x = walls[0].y = walls[3].y = 10;

        robots_.clear();
    }

    // the target draws a cardoid curve
    void Environment::updateTarget()
    {
        double c = -cos(0.0005*iter),
                s = -sin(0.0005*iter);
        double a = 6, b = 10;
        target.x = (a + b*c)*c+a+1-b;
        target.y = (a + b*c)*s;

        x_hist.push_back(target.x);
        y_hist.push_back(target.y);
        iter++;
    }

    void Environment::addRobot(Robot &_robot)
    {
        robots_.push_back(&_robot);
    }

    void Environment::plotTrajectory(std::string name_, std::vector<double> x_, std::vector<double> y_, std::string color_)
    {

        matplotlibcpp::named_plot(name_, x_, y_,color_);
        // start and end positions
        std::vector<double> x_start = {x_[0]},
                y_start = {y_[0]},
                x_end = {x_[x_.size()-1]},
                y_end = {y_[y_.size()-1]};
        matplotlibcpp::plot(x_start, y_start, color_+"D");
        matplotlibcpp::plot(x_end, y_end, color_+"s");
    }


    // plots the trajectory in the given environment
    void Environment::plot()
    {
        std::vector<double> x,y;
        std::vector<std::string> colors = {"b","g","r","c"};

        // plot target motion
        plotTrajectory("Target", x_hist, y_hist, "m");

        unsigned int i=0;
        for(auto &robot: robots_)
        {
            robot->getHistory(x,y);
            plotTrajectory(robot->name(), x, y, colors[i]);
            ++i;
        }

        matplotlibcpp::named_plot("Initial poses", std::vector<double>(), std::vector<double>(), "kD");
        matplotlibcpp::named_plot("Final poses", std::vector<double>(), std::vector<double>(), "ks");
        matplotlibcpp::legend();

        // plot environment
        // walls
        if(walls.size() > 0)
        {
            x.resize(walls.size());
            y.resize(walls.size());
            for(unsigned int i=0;i<walls.size();++i)
            {
                x[i] = walls[i].x;
                y[i] = walls[i].y;
            }

            double  x_min = *(std::min_element(x.begin(), x.end())),
                    x_max = *(std::max_element(x.begin(), x.end())),
                    y_min = *(std::min_element(y.begin(), y.end())),
                    y_max = *(std::max_element(y.begin(), y.end()));

            // invisible plot just for size
            std::vector<double> x_minmax(2), y_minmax(2);
            x_minmax[0] = x_min - .05*(x_max - x_min);
            x_minmax[1] = x_max + .05*(x_max - x_min);
            y_minmax[0] = y_min - .05*(y_max - y_min);
            y_minmax[1] = y_max + .05*(y_max - y_min);
            matplotlibcpp::plot(x_minmax, y_minmax, "w.");

            x.push_back(x[0]);
            y.push_back(y[0]);
            matplotlibcpp::plot(x, y, "k");
        }

        matplotlibcpp::show();
    }
}
