cmake_minimum_required(VERSION 2.8)
project(arpro_robot)
# Python to plot robot trajectory
find_package(PythonLibs REQUIRED)

add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)

# all include libraries
include_directories(${PYTHON_INCLUDE_DIRS}
                    include
)

# Robot library
add_library(lab2 SHARED src/robot.cpp include/robot.h include/geom.h
                        include/envir.h src/envir.cpp
                        include/sensor.h
                        )

# Lab 1: using the robot class
# Lab 2: sensors on robot
add_executable(move_robot src/main.cpp)
target_link_libraries(move_robot lab2 ${PYTHON_LIBRARIES})
