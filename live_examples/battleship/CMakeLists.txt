project(battleship)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(battleship main.cpp src/player.cpp)

