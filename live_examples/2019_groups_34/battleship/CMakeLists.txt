 
# CMakeLists.txt

project(battleship)

set(CMAKE_CXX_STANDARD 11)

add_executable(battleship battleship.cpp
                          player.h player.cpp
                          cell.h)

