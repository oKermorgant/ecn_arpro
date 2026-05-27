#include <treasure_hunt_ai.h>
#include <duels/utils/grid_point.h>

#include <duels/algo/a_star.h>

constexpr int FREE{0};
constexpr int ROCK{1};
constexpr int UNKNOWN{2};

TreasureHuntAI::TreasureHuntAI()
  : map(20, 30, UNKNOWN) // fill the 20x30 map with 2's (unknown)
{
  // register this map for all grid points
  pose.setMap(map);

  // TODO the treasure may be at any position: update candidates

}

Action TreasureHuntAI::computeFrom(const Feedback &feedback)
{
  // register where we are
  pose.set(feedback.pose);
  // if we are here then it is not a treasure position
  removeCandidate(pose);

  // TODO process feedback.scan to update map


  // TODO process feedback.treasure_distance to update candidates
  // as we compare floating points, a small threshold is useful to tell if two values are equal  
  // pruneCandidates();


  // TODO use A* to find shortest path to first candidate, will assume unknown cells are free


  // TODO identify which move from pose to next


  return Action::TURN_LEFT;


}
