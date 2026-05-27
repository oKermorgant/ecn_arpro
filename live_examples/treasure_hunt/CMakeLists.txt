cmake_minimum_required(VERSION 3.15)
project(treasure_hunt CXX)

SET(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels installation folder")

if(NOT EXISTS ${DUELS_ROOT})
  # try home directory or assume relative path
  if(EXISTS("$ENV{HOME}/duels"))
SET(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels installation folder")
  else()
SET(DUELS_ROOT "/opt/duels" CACHE STRING "Path to duels installation folder")
  endif()
endif()
message(STATUS "Using ${DUELS_ROOT} as framework base folder")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# find ZeroMQ and yaml-cpp for message passing
find_path ( ZMQ_INCLUDE_DIR zmq.h )
find_library ( ZMQ_LIBRARY NAMES zmq )
find_package(yaml-cpp)

include_directories(${DUELS_ROOT}/include ${ZMQ_INCLUDE_DIR} ${YamlCpp_INCLUDE_DIRS} include)
add_definitions(-DDUELS_BIN_PATH="${DUELS_ROOT}/bin")

# add whatever additional includes / libs needed for your AI

add_executable(treasure_hunt treasure_hunt.cpp src/treasure_hunt_ai.cpp)
target_link_libraries(treasure_hunt ${ZMQ_LIBRARY} yaml-cpp)