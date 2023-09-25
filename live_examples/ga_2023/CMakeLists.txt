project(genetic)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

find_package(yaml-cpp)
include_directories(include)

add_executable(xy xy.cpp)

add_executable(travel travel.cpp)
target_link_libraries(travel yaml-cpp)
