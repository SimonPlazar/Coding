cmake_minimum_required(VERSION 3.21)
project(Vaja2Algoritmi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Vaja2Algoritmi Vaja2Algoritmi.cpp)
