 project(battleship)
 add_compile_options(-std=c++11)


 add_executable(battleship main.cpp
   player.h
   player.cpp)
