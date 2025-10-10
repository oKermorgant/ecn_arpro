project(ga)

include_directories(include)
add_executable(rastrigin rastrigin.cpp
  include/rand_utils.h)
