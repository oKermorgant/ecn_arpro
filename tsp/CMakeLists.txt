project(tsp)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YamlCpp yaml-cpp)

include_directories(include ${YamlCpp_INCLUDE_DIRS})

add_executable(tsp main/tsp.cpp
    include/travel.h src/travel.cpp
    include/ga.h
    include/interface.h
    include/rand_util.h src/rand_util.cpp)
target_link_libraries(tsp yaml-cpp)
