cmake_minimum_required(VERSION 3.20)

project(esercitazione2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(array_address array_address.cpp)

add_executable(analisi_array analisi_array.cpp)

add_executable(bubblesort_naive bubblesort_naive.cpp)
