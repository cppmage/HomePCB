cmake_minimum_required(VERSION 3.3)
project(HomePCB )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
find_package(Boost COMPONENTS  program_options filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(csmv "../CreateSortedMovementVector.cpp" "../csmv.cpp" "../vsort.cpp" )
target_link_libraries(csmv ${Boost_LIBRARIES})
