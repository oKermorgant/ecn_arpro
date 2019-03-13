cmake_minimum_required(VERSION 3.4)
project(ecn_arpro)


set(CMAKE_CXX_STANDARD 11)

find_package(PythonLibs 2.7)

# all include libraries
include_directories(include ${PYTHON_INCLUDE_DIRS})

# Robot library
add_library(lab2 SHARED src/robot.cpp include/robot.h include/geom.h
                        include/envir.h src/envir.cpp
                        include/sensor.h)
target_link_libraries(lab2  ${PYTHON_LIBRARIES})

# Lab 3: using the robot class
# Lab 4: sensors on robot
add_executable(move_robot src/main.cpp)
target_link_libraries(move_robot lab2)
