cmake_minimum_required(VERSION 3.1)
project(genetic)
set(CMAKE_CXX_STANDARD 17)

find_package(yaml-cpp)
include_directories(include)

add_executable(xy xy.cpp)

add_definitions(-DTSP_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(travel travel.cpp)
target_link_libraries(travel yaml-cpp)

add_executable(pointers pointers.cpp)
