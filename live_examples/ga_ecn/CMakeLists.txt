cmake_minimum_required (VERSION 2.6)
project (ga)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

find_package(PkgConfig)
pkg_check_modules(YamlCpp yaml-cpp)
include_directories(${YamlCpp_INCLUDE_DIRS})

add_executable(tsp main.cpp ga.h travel.h ga_opt.h)
target_link_libraries(tsp yaml-cpp)