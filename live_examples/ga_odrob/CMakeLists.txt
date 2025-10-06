project(ga)

include_directories(include)

add_executable(rastrigin rastrigin.cpp
  include/xy.h
  include/ga.h)

