#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <envir.h>
#include <robot.h>

using std::endl;using std::cout;

namespace arpro
{

class Sensor
{
public:
    // basic constructor
    Sensor(Robot &_robot, double _x, double _y, double _theta)
    {
        s_ = 0;
        s_history_.clear();
        robot_ = &_robot;
        pose_ = Pose(_x, _y, _theta);
        _robot.attach(this);
    }

    inline static void setEnvironment(Environment &_envir) {envir_ = &_envir;}

    // update from current sensor pose
    virtual void update(const Pose &_p) = 0;

    // update from current robot pose
    void updateFromRobotPose(const Pose &_p)
    {
        update(pose_.transformDirect(_p));
    }

    // correct twist in sensor frame
    virtual void correctTwist(Twist &_v) {}

    // correct twist in robot frame
    void correctRobotTwist(Twist &_v)
    {
        cout << " Correction new sensor" << endl;
        cout << "     Base robot twist: " << _v << endl;
        // twist in sensor frame
        _v = _v.transformInverse(pose_);
        cout << "     Base sensor twist: " << _v << endl;

        // check twist in sensor frame
        correctTwist(_v);
        cout << "     Corrected sensor twist: " << _v << endl;

        // back to robot frame
        _v = _v.transformDirect(pose_);
        cout << "     Corrected robot twist: " << _v << endl;
    }

    // read current measurement
    double read() {return s_;}

protected:
    // current measurement
    double s_;
    // measurement history
    std::vector<double> s_history_;
    static Environment* envir_;
    // pose in robot frame
    Pose pose_;
    Robot* robot_;
};
}



#endif // SENSOR_H
