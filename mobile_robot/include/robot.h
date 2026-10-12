#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <geom.h>

namespace arpro
{

class Sensor;

class Robot
{
public:
    // initialize robot at (x,y,theta)
    Robot(std::string _name, double _x, double _y, double _theta);
    void setSamplingTime(double dt)
    {
      dt_ = dt;
    }

    Pose pose() {return pose_;}

    // attach a sensor
    void attach(Sensor *_sensor)
    {
        sensors_.push_back(_sensor);
    }
    
    // move robot with a given (x,y,theta) velocity
    void moveXYT(double _vx, double _vy, double _omega);

    // move robot with linear and angular velocities
    void moveVW(double _v, double _omega);
        
    // move robot with given wheel velocity
    void rotateWheels(double _left, double _right);

    // try to go to a given (x,y) position with sensor constraints
    void goTo(const Pose &_p);

    //try to follow a local frame velocity with sensor constraints
    void moveWithSensor(Twist _twist);
    
    // prints the current position
    void printPosition();

    inline void getHistory(std::vector<double> &_x, std::vector<double> &_y) const
    {
        _x = x_history_;
        _y = y_history_;
    }

    inline std::string name() const {return name_;}

protected:
    // position
    Pose pose_;
    std::vector<double> x_history_, y_history_;
    std::string name_;

    // sampling time
    double dt_ = 0.1;

    // sensors
    std::vector<Sensor*> sensors_;
};

}

#endif
