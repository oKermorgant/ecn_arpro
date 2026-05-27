#ifndef BOAT_NODE_H
#define BOAT_NODE_H

#include <duels/treasure_hunt/msg.h>
#include <duels/utils/grid_point.h>
#include <algorithm>

using namespace duels;
using namespace duels::treasure_hunt;

class BoatNode : public GridPoint
{
  using BoatNodePtr = std::unique_ptr<BoatNode>;
public:

  BoatNode(int _x=0, int _y=0, Orientation _t = Orientation::LEFT) : GridPoint(_x, _y), orientation(_t) {}

  inline void set(const Pose2D &pose)
  {
    x = pose.x;
    y = pose.y;
    orientation = pose.orientation;
  }

  inline bool operator==(const BoatNode &other) const
  {
    return x==other.x && y==other.y && orientation==other.orientation;
  }

  inline duels::Vector2D<int> forwardPosition() const
  {
    return *this + orientation.fwd();
  }

  std::vector<BoatNodePtr> children() const
  {
    std::vector<BoatNodePtr> out;
    out.reserve(3);
    out.push_back(std::make_unique<BoatNode>(x, y, orientation.toLeft()));
    out.push_back(std::make_unique<BoatNode>(x, y, orientation.toRight()));

    const auto &[xp, yp] = forwardPosition(); {}
    if(grid->cell(xp, yp) != 1)
    out.push_back(std::make_unique<BoatNode>(xp, yp, orientation));
    return out;
  }

  Orientation orientation;
};


#endif // BOAT_NODE_H
