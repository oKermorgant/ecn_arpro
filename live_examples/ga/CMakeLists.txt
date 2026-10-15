cmake_minimum_required (VERSION 3.15)
project(ga)

add_compile_options(-pthread)

#find_package (Threads)
# find_package(TBB COMPONENTS tbb)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_executable(ga ga.cpp src/point.cpp
  include/ga.h)

# target_link_libraries(ga tbb)
