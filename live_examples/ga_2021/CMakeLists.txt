project(genetic_algo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include_directories(.)
add_executable(rastrigin rastrigin.cpp)
