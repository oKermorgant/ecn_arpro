cmake_minimum_required(VERSION 3.4)
project(ecn_arpro)

# Python to plot robot trajectory
execute_process(COMMAND python2-config --includes OUTPUT_VARIABLE PYTHON_INCLUDE_FLAGS)
SET(CXX_INCLUDES ${CXX_INCLUDES} ${PYTHON_INCLUDE_FLAGS})
set(CMAKE_CXX_STANDARD 11)

# all include libraries
include_directories(include)


# Robot library
add_library(lab2 SHARED src/robot.cpp include/robot.h include/geom.h
                        include/envir.h src/envir.cpp
                        include/sensor.h)
target_link_libraries(lab2 "-lpython2.7")

# Lab 3: using the robot class
# Lab 4: sensors on robot
add_executable(move_robot src/main.cpp)
target_link_libraries(move_robot lab2)
