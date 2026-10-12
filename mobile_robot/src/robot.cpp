

#include <iostream>
#include <math.h>
#include <robot.h>
#include <sensor.h>

using namespace arpro;
using namespace std;

Environment* Sensor::envir_ = nullptr;

Robot::Robot(string _name, double _x, double _y, double _theta)
{    
    pose_.x = _x;
    pose_.y = _y;
    pose_.theta = _theta;

    name_ = _name;

    // init position history
    x_history_.push_back(_x);
    y_history_.push_back(_y);
}


void Robot::moveXYT(double _vx, double _vy, double _omega)
{
    // update position
    pose_.x += _vx*dt_;
    pose_.y += _vy*dt_;
    pose_.theta += _omega*dt_;

    // store position history
    x_history_.push_back(pose_.x);
    y_history_.push_back(pose_.y);
}



void Robot::rotateWheels(double _left, double _right)
{
    // to fill up after defining an initWheel method






}


// move robot with linear and angular velocities
void Robot::moveVW(double _v, double _omega)
{
    // to fill up

}




// try to go to a given x-y position
void Robot::goTo(const Pose &_p)
{
    // error in robot frame
    Pose error = _p.transformInverse(pose_);

    // try to do a straight line with sensor constraints
    moveWithSensor(Twist(error.x, error.y, 0));
}


void Robot::moveWithSensor(Twist _twist)
{
    // to fill up, sensor measurement and twist checking



    // uses X-Y motion (perfect but impossible in practice)
    moveXYT(_twist.vx, _twist.vy,_twist.w);

    // to fill up, use V-W motion when defined
}


void Robot::printPosition()
{
    cout << "Current position: " << pose_.x << ", " << pose_.y << endl;
}

