#include <iostream>
#include <math.h>
#include <cmath>

#include <robot.h>
#include <envir.h>
#include <sensor.h>

using namespace std;
using namespace arpro;



int main()
{
    // default environment with moving target
    Environment envir;
    // sensors gets measurements from this environment
    Sensor::setEnvironment(envir);

    // init robot at (0,0,0)
    Robot robot("R2D2", 0,0,0);    
    envir.addRobot(robot);


    for(unsigned int i=0;i<10000;++i)
    {
        cout << "---------------------" << endl;

        // update target position
        envir.updateTarget();        

        // try to follow target
        robot.goTo(envir.target);

    }

    // plot trajectory
    envir.plot();
    
}
