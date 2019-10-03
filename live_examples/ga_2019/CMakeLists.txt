project(genetic_algo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
 
add_executable(xy solve_xy xy.h xy.cpp
  ga.h)
