cmake_minimum_required(VERSION 2.8)
project(arpro_robot_sols)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

# basic exercises
add_executable(find_the_number basics/find_the_number.cpp)
add_executable(rps basics/rps.cpp)

# Battleship
add_executable(battleship battleship/player.h battleship/player.cpp
                          battleship/main.cpp
                          battleship/cell.h )


# 1 vs 1 game with alpha-beta algorithm
add_executable(tictactoe alpha_beta/alpha_beta.h alpha_beta/alpha_beta_game.h alpha_beta/tictactoe_config.h alpha_beta/tictactoe.cpp)
add_executable(four_in_a_row alpha_beta/alpha_beta.h alpha_beta/alpha_beta_game.h alpha_beta/four_in_a_row_config.h alpha_beta/four_in_a_row.cpp)

# minimization
add_executable(scalar minimization/scalar.cpp)
add_executable(nD_function minimization/nd_function.cpp minimization/nd_vector.h)

# A* algorithm
add_executable(puzzle a_star/puzzle.cpp a_star/puzzle.h a_star/a_star.h)
add_executable(missionaries_cannibals a_star/missionaries_cannibals.cpp a_star/missionaries_cannibals.h a_star/a_star.h)

# Genetic Algorithm with multi-thread
add_executable(function_ga ga/function_indiv.h ga/genetic_algo.h ga/main.cpp)
target_link_libraries(function_ga ${CMAKE_THREAD_LIBS_INIT})

# Numbers made of 6 6's
add_executable(find666666 666666/find666666.cpp)

# Hanoi puzzle
add_executable(hanoi hanoi/hanoi.cpp)

# 21 sticks
add_executable(sticks sticks/sticks.cpp)
add_executable(sticks_ab alpha_beta/alpha_beta.h alpha_beta/alpha_beta_game.h sticks/sticks_config.h sticks/sticks_alpha_beta.cpp)
