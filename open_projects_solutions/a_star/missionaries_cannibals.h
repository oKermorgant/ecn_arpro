#ifndef MISSIONARIES_CANNIBALS_H
#define MISSIONARIES_CANNIBALS_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

// what is this puzzle
class MissionariesCannibals
{

  typedef std::unique_ptr<MissionariesCannibals> Ptr;
  typedef std::vector<Ptr> Vector;

public:
  // default constructor
  MissionariesCannibals(int missionaries, int cannibals, bool left_side = true) :
    missionaries_left(missionaries),
    cannibals_left(cannibals),
    boat_left(left_side)
  {
    if(missionaries_total == 0 || cannibals_total == 0)
    {
      missionaries_total = missionaries;
      cannibals_total = cannibals;
      boatSize(2);
    }
  }

  MissionariesCannibals(): MissionariesCannibals(0,0,false) {}

  void boatSize(int n)
  {
    moves.clear();
    for(int i = 0; i <= n; ++i)
    {
      for(int j = 0; j <= n; ++j)
      {
        if(i+j > 0 && i+j <= n)
          moves.push_back({i,j});
      }
    }
  }

  void print(MissionariesCannibals* parent = nullptr) const
  {
    if(parent)
    {
      // print the move to go from parent to this
      std::stringstream ss;
      ss << "_";
      for(int i = 0; i < std::min(missionaries_left,parent->missionaries_left); ++i)
        ss << "M";
      for(int i = 0; i < std::min(cannibals_left,parent->cannibals_left); ++i)
        ss << "C";
      if(boat_left)
        ss << "_ ~~~ <- \\_";
      else
        ss << "_ \\_";
      for(int i = 0; i < std::abs(missionaries_left-parent->missionaries_left); ++i)
        ss << "M";
      for(int i = 0; i < std::abs(cannibals_left-parent->cannibals_left); ++i)
        ss << "C";
      if(boat_left)
        ss << "_/ _";
      else
        ss << "_/ -> ~~~ _";
      for(int i = 0; i < std::min(missionaries_total- missionaries_left,
                                  missionaries_total-parent->missionaries_left); ++i)
        ss << "M";
      for(int i = 0; i < std::min(cannibals_total-cannibals_left
                                  ,cannibals_total-parent->cannibals_left); ++i)
        ss << "C";
      ss << "_";
      std::cout << std::endl << ss.str() << std::endl;
    }
  }


  bool is(const MissionariesCannibals & goal)
  {
    return missionaries_left == goal.missionaries_left &&
        cannibals_left == goal.cannibals_left &&
        boat_left == goal.boat_left;
  }


  Vector children()
  {

    //  std::cout << "M: " << missionaries_left << ", C: " << cannibals_left << ", side=" << boat_left << '\n';

    Vector ret;
    // how many are leaving
    for(const auto & move: moves)
    {
      // how many are staying
      const int m = (boat_left?missionaries_left:(missionaries_total-missionaries_left)) - move.first;
      const int c = (boat_left?cannibals_left:(cannibals_total-cannibals_left)) - move.second;

      if(m >= 0 && c >= 0 && (c == 0 || m <= c))
      {
        // std::cout << "  ok for dm = " << move.first << " and dc = " << move.second << std::endl;
        //  std::cout << " -> m = " << m << ", c = " << c << std::endl;
        if(boat_left)
          ret.push_back(Ptr(new MissionariesCannibals(m,
                                                      c,
                                                      !boat_left)));
        else
          ret.push_back(Ptr(new MissionariesCannibals(missionaries_total-m,
                                                      cannibals_total- c,
                                                      true)));
      }
      //    else
      //     std::cout << "  not ok for dm = " << move.first << " and dc = " << move.second << std::endl;
    }
    return ret;
  }

  int h(const MissionariesCannibals &goal)
  {
    return missionaries_left + cannibals_left;
  }

  int distToParent() {return 1;}

protected:
  static int missionaries_total, cannibals_total;
  int missionaries_left, cannibals_left;
  bool boat_left = true;
  static std::vector<std::pair<int,int>> moves;
};

int MissionariesCannibals::missionaries_total;
int MissionariesCannibals::cannibals_total;
std::vector<std::pair<int,int>> MissionariesCannibals::moves;

#endif // MISSIONARIES_CANNIBALS_H
