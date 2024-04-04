cmake_minimum_required(VERSION 3.22)
project(Numa_Analysis)

add_executable(cores.out ./src/cores.cpp)
add_link_options(cores.out numa)


find_library(NUMA_LIBRARY numa)
target_link_libraries(cores.out ${NUMA_LIBRARY})