#ifndef TREASUREHUNTAI_H
#define TREASUREHUNTAI_H

#include "boat_node.h"
#include <functional>

class TreasureHuntAI
{
public:
  TreasureHuntAI();

  Action computeFrom(const Feedback &feedback);


private:
  BoatNode pose;
  Grid map;

  std::vector<Vector2D<int>> candidates;
  inline void removeCandidate(Vector2D<int> xy)
  {
    const auto pos = std::find(candidates.begin(), candidates.end(), xy);
    if(pos != candidates.end())
      candidates.erase(pos);
  }
  
  // erase-remove and exception from pruning candidates
  void pruneCandidates(const std::function<bool(const Vector2D<int>&)> &crit)
  {
    candidates.erase(std::remove_if(candidates.begin(), candidates.end(), crit),
                     candidates.end());
    if(candidates.empty())
      throw std::out_of_range("pruneCandidates: No more treasure candidates: check your erase criterion");
  }

  // do not hesitate to define new methods to avoid having a big computeFrom function

};

#endif // TREASUREHUNTAI_H
