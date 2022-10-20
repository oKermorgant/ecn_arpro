project(genetic_algo)


#add_definitions(GA_SOURCE ${CMAKE_SOURCE_DIR})

find_package(yaml-cpp)

include_directories(include)
add_executable(xy_test src/xy_test.cpp)
add_executable(xy_ga src/xy_ga.cpp)

add_executable(tsp src/tsp.cpp src/travel.cpp)
target_link_libraries(tsp yaml-cpp)

# also use pybind to compare against Python version
find_package(pybind11)
if(pybind11_FOUND)
    pybind11_add_module(tsp_pb SHARED src/tsp.cpp src/tsp_pybind.cpp)
    set_target_properties(tsp_pb PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
