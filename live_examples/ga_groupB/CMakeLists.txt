cmake_minimum_required (VERSION 2.6)
project (ga)
add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

find_package(PkgConfig)
pkg_check_modules(YamlCpp yaml-cpp)
include_directories(${YamlCpp_INCLUDE_DIRS})

add_executable(ga main.cpp individual.h ga.h)

add_executable(tsp tsp.cpp travel.h ga.h)
target_link_libraries(tsp ${YamlCpp_LIBRARIES})
