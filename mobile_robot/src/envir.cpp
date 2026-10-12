#include <vector>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <robot.h>
#include <envir.h>
#include <fstream>

namespace arpro
{

Environment::Environment()
{
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
  double c = -cos(0.05*t),
      s = -sin(0.05*t);
  double a = 6, b = 10;
  target_.x = (a + b*c)*c+a+1-b;
  target_.y = (a + b*c)*s;

  x_hist.push_back(target_.x);
  y_hist.push_back(target_.y);

  t += dt;
}

void Environment::addRobot(Robot &_robot)
{
  _robot.setSamplingTime(dt);
  robots_.push_back(&_robot);
}

void copyToCoord(std::vector<double> &coord, const std::vector<double> &src,
                 uint & offset)
{
  std::copy(src.begin(), src.end(), coord.begin() + offset);
  offset += src.size();
}

template <class T>
void writeYAMLine(std::ofstream &out,
                  std::string key,
                  const std::vector<T> &data
                  )
{
  out << key << " [";
  for(uint i = 0; i < data.size(); ++i)
  {
    out << data[i];
    if(i != data.size()-1)
      out << ", ";
  }
  out << "]\n";
}


// plots the trajectory in the given environment
void Environment::plot()
{
  const uint size = x_hist.size();
  const uint n_traj = 1 + robots_.size();

  const std::vector<std::string> colors{"m", "b","g","r","c"};

  std::vector<double> coord(size * n_traj * 2);
  std::vector<std::string> names(n_traj);

  uint offset = 0;
  names[0] = "Target";
  copyToCoord(coord, x_hist, offset);
  copyToCoord(coord, y_hist, offset);

  uint n=1;
  std::vector<double> x,y;
  for(auto &robot: robots_)
  {
    robot->getHistory(x,y);
    x.resize(size);
    y.resize(size);
    copyToCoord(coord, x, offset);
    copyToCoord(coord, y, offset);
    names[n] = robot->name();
    ++n;
  }

  std::ofstream out("data.yaml");
  writeYAMLine(out, "names:", names);
  writeYAMLine(out, "colors:", colors);

  out << "data: \n";
  std::vector<double> line(2*n_traj);
  for(uint i = 0; i < size; ++i)
  {
    for(uint robot = 0; robot< n_traj; robot++)
    {
      line[2*robot] = coord[2*robot*size + i];
      line[2*robot+1] = coord[(2*robot+1)*size + i];
    }
    writeYAMLine(out, "    -", line);
  }

  if(walls.size() > 0)
  {
    x.clear();
    y.clear();
    for(auto &w: walls)
    {
      x.push_back(w.x);
      y.push_back(w.y);
    }
    out << "walls:\n";
    writeYAMLine(out, "    x:", x);
    writeYAMLine(out, "    y:", y);
  }
  out.close();

  std::stringstream ss;
  ss << "python3 " << SCRIPT_PATH << " data.yaml";
  system(ss.str().c_str());
}
}
