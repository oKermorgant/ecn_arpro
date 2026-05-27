project(ga)

find_library(TBB COMPONENT tbb)
include_directories(include)
add_executable(rastrigin rastrigin.cpp
  include/rand_utils.h)
target_link_libraries(rastrigin tbb)
