cmake_minimum_required(VERSION 3.5)
project(sudoku)

add_definitions(-DSUDOKU_BASE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(yaml-cpp)
find_package(OpenCV)

if(yaml-cpp_FOUND)
  add_definitions(-DSUDOKU_WITH_YAML)
endif()
if(OpenCV_FOUND)
  add_definitions(-DSUDOKU_WITH_OPENCV)
  set(OpenCV_LIB opencv_highgui)
endif()

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE Debug)

add_executable(sudoku main.cpp src/cell.cpp include/sudoku/grid.h src/grid.cpp src/grid_display.cpp
  )
target_include_directories(sudoku PRIVATE include
  ${YamlCpp_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS})

target_link_libraries(sudoku yaml-cpp ${OpenCV_LIB})









