#ifndef FLEET_ROBOT
#define FLEET_ROBOT

#include <random>
#include <ostream>

inline auto randf()
{
  static const auto scale{10};
  static auto gen{std::default_random_engine()};
  static auto distribution{std::uniform_int_distribution(-5*scale,5*scale)};
  return double(distribution(gen))/scale;
}


struct Robot
{
  inline static int initialized{};
  double x{randf()}, y{randf()};
  std::string name{"R2D" + std::to_string(++initialized)};

  friend auto& operator<<(std::ostream& os, const Robot &robot)
  {
    os << robot.name << " @ (" << robot.x << ", " << robot.y << ")";
    return os;
  }

  double distance(double x, double y) const;
};

#endif
