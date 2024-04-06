cmake_minimum_required(VERSION 3.22)
project(Numa_Analysis)

find_library(NUMA_LIBRARY numa)
find_package(OpenMP COMPONENTS CXX REQUIRED)

add_executable(cores.out ${CMAKE_CURRENT_SOURCE_DIR}/src/cores.cpp)
target_link_libraries(cores.out PRIVATE OpenMP::OpenMP_CXX ${NUMA_LIBRARY})