cmake_minimum_required(VERSION 3.0)
project(n-queens)

set(CMAKE_CXX_STANDARD 14)

if (NOT DEFINED NB_QUEENS)
    set(NB_QUEENS 8)
endif ()

add_executable(n_queens main.cpp)
set_target_properties(n_queens PROPERTIES COMPILE_DEFINITIONS "NB_QUEENS=${NB_QUEENS}")
