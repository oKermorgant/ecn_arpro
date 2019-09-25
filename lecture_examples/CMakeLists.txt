cmake_minimum_required (VERSION 2.6)
project (ARPRO_examples)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-pthread)

set(CMAKE_BUILD_TYPE Release)

find_package (Threads)
find_package(PkgConfig)
pkg_check_modules(YamlCpp yaml-cpp)
find_package(VISP)

include_directories(.)

add_executable(hello hello.cpp)
add_executable(forloop forloop.cpp)
add_executable(whileloop whileloop.cpp)
add_executable(switchcase switchcase.cpp)
add_executable(scope scope.cpp)
add_executable(profiling profiling.cpp)
add_executable(chrono chrono.cpp)
add_executable(debug debug.cpp)
add_executable(function function.cpp)
add_executable(smart_ptr smart_ptr.cpp)
add_executable(pointers pointers.cpp)
add_executable(class class.cpp)

#add_executable(exception exception.cpp)

if(YamlCpp_FOUND)
  include_directories(${YamlCpp_INCLUDE_DIRS})
    add_executable(config config.cpp)
    target_link_libraries(config yaml-cpp)
    add_executable(lambda lambda.cpp)
    add_executable(algorithm algorithm.cpp)
    add_executable(inheritance inheritance.cpp)
    add_executable(templates templates.cpp)
    add_executable(templates2 templates2.cpp)
endif()

if(VISP_FOUND)
  add_executable(debug_visp debug_visp.cpp)
  target_include_directories(debug_visp PRIVATE ${VISP_INCLUDE_DIRS})
  target_link_libraries(debug_visp ${VISP_LIBRARIES})
endif()

add_executable(thr thr.cpp)
target_link_libraries(thr ${CMAKE_THREAD_LIBS_INIT})
