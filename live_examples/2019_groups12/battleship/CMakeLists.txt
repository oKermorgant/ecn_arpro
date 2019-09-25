# name of the file:  CMakeLists.txt

project(battleship)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

add_executable(battleship battleship.cpp player.h player.cpp cell.h)
