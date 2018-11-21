cmake_minimum_required(VERSION 3.4)
project(ecn_arpro)

# Python to plot robot trajectory
execute_process(COMMAND python2-config --includes OUTPUT_VARIABLE PYTHON_INCLUDE_FLAGS)

add_compile_options(-std=c++11)

# all include libraries
include_directories(include)
SET(CXX_INCLUDES ${CXX_INCLUDES} ${PYTHON_INCLUDE_FLAGS})

# Robot library
add_library(lab2 src/robot.cpp include/robot.h include/geom.h
                        include/envir.h src/envir.cpp
                        include/sensor.h include/sensor_range.h
                        include/sensor_bearing.h
                        )
target_link_libraries(lab2 "-lpython2.7")

# Lab 3: using the robot class
# Lab 4: sensors on robot
add_executable(move_robot src/main.cpp)
target_link_libraries(move_robot lab2)
