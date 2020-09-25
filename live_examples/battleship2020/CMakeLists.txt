project(Battleship)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(battleship
  include/player.h src/player.cpp
  include/boat.h
  src/main.cpp)
