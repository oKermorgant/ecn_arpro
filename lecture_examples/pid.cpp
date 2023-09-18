#include <iostream>

struct PID
{
  double Kp = .1, Ki = .2, Kd = .4;
};

int main(int argc, char** argv)
{

  std::cout << "Nb of arguments: " << argc << std::endl;

  PID pid;

  if(argc > 1)
    pid.Kp = atof(argv[1]);
  if(argc > 2)
    pid.Ki = atof(argv[2]);


  std::cout << "Kp = " << pid.Kp << std::endl;





}
