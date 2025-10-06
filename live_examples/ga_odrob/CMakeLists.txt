cmake_minimum_required(VERSION 3.5)
project(ga)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(rastrigin rastrigin.cpp
  include/xy.h
  include/ga.h
  include/rand_utils.h)

