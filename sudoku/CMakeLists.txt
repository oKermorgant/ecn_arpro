cmake_minimum_required(VERSION 3.4)
project(sudoku)

add_definitions(-DSUDOKU_BASE_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(yaml-cpp)

if(yaml-cpp_FOUND)
  add_definitions(-DSUDOKU_WITH_YAML)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(sudoku main.cpp include/sudoku/cell.h src/cell.cpp include/sudoku/grid.h src/grid.cpp)
target_include_directories(sudoku PRIVATE include ${YamlCpp_INCLUDE_DIRS})
target_link_libraries(sudoku yaml-cpp)
