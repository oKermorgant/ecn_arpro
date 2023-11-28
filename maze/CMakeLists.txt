cmake_minimum_required (VERSION 2.6)
project (maze)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

find_package(yaml-cpp)

add_definitions(-DMAZES="${CMAKE_CURRENT_SOURCE_DIR}/mazes")

include_directories(${YamlCpp_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} include)

add_library(maze SHARED include/maze.h include/a_star.h
    include/point.h src/point.cpp)
target_link_libraries(maze ${OpenCV_LIBS})

#add_executable(generator src/generator.cpp)
#target_link_libraries(generator maze)

#add_executable(line src/solve_line.cpp)
#target_link_libraries(line maze)

add_executable(cell src/solve_cell.cpp)
target_link_libraries(cell  maze)

#add_executable(corridor src/solve_corridor.cpp)
#target_link_libraries(corridor maze)
