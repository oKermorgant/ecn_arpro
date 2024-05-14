#ifndef SUDOKU_STARTING_GRIDS_H
#define SUDOKU_STARTING_GRIDS_H

#ifdef SUDOKU_WITH_YAML
#include <yaml-cpp/yaml.h>
#include <filesystem>
#endif
#include <array>
#include <algorithm>
#include <string>
#include <stdexcept>

inline bool useDisplay(int argc, char** argv, bool display)
{
  if(std::any_of(argv, argv+argc,[](const std::string &arg){return arg == "-d";}))
    return true;
  if(std::any_of(argv, argv+argc,[](const std::string &arg){return arg == "-n";}))
    return false;
  return display;
}


// starting grid depending on whether we have YAML

using StartingGrid = std::array<std::array<uint,9>,9>;

inline StartingGrid getStart(int argc, char** argv, std::string start)
{
  if(argc > 1)
    start = argv[1];

#ifndef SUDOKU_WITH_YAML
  // cannot read YAML, ballback to hard-coded starts
  if(start == "easy")
  {
    return {{
        {0, 7, 0, 6, 0, 0, 3, 0, 1},
        {9, 0, 0, 0, 7, 5, 0, 0, 0},
        {1, 8, 6, 0, 0, 0, 0, 0, 2},
        {0, 4, 3, 7, 6, 0, 5, 0, 0},
        {0, 0, 0, 3, 0, 4, 0, 8, 0},
        {0, 5, 7, 9, 2, 0, 1, 0, 0},
        {7, 6, 5, 0, 0, 0, 0, 0, 8},
        {4, 0, 0, 0, 3, 7, 0, 0, 0},
        {0, 9, 0, 8, 0, 0, 2, 0, 5}}};
  }
  if(start == "medium")
  {
    return {{
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 6, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 0, 0},
        {2, 0, 9, 0, 0, 0, 0, 0, 7},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}}};
  }
  if(start == "harder")
  {
    return {{
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 8, 5},
        {0, 0, 1, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 7, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 1, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 7, 3},
        {0, 0, 2, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 9}}};

  }
  if(start == "hard")
  {
    return {{
        {0, 8, 0, 1, 0, 0, 0, 2, 0},
        {0, 0, 0, 9, 0, 0, 0, 5, 0},
        {9, 7, 2, 0, 0, 0, 0, 6, 0},
        {4, 0, 0, 0, 2, 6, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 7, 0, 0},
        {8, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 9, 5, 0, 0, 0},
        {0, 2, 5, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 4, 0, 0, 0, 1}}};
  }
  if(start == "basic0")
  {
    return {{
        {5,3,4,6,7,8,9,1,2},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,5},
        {3,4,5,2,8,6,1,7,9}}};
  }
  if(start == "basic1")
  {
    return {{
        {5,3,4,6,7,8,9,1,0},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,5},
        {3,4,5,2,8,6,1,7,9}}};
  }
  if(start == "basic2")
  {
    return {{
        {5,3,4,6,7,8,9,1,0},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,5},
        {0,4,5,2,8,6,1,7,9}}};
  }
  if(start == "bug")
  {
    return {{
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}}};
  }

  // cannot read files anyway
  throw std::invalid_argument("Given starting grid (" + start + ") is not known");
#else

  // not hard-coded -> must exist
  if(!std::filesystem::exists(start))
  {
    // maybe a local starting grid
    const auto local_start = SUDOKU_BASE_PATH + ("/starts/" + start + ".yaml");
    if(std::filesystem::exists(local_start))
      start = local_start;
    else
      throw std::invalid_argument("Given starting grid (" + start + ") does not exist");
  }

  StartingGrid grid;
  auto config = YAML::LoadFile(start);

  // build grid
  uint row = 0;
  for(const auto &line: config)
  {
    uint col = 0;
    for(const auto &elem: line)
    {
      if(elem.as<std::string>() != ".")
        grid[row][col] = elem.as<uint>();
      else
        grid[row][col] = 0;
      col++;
    }
    row++;
  }
  return grid;
#endif
}


#endif // SUDOKU_STARTING_GRIDS_H
