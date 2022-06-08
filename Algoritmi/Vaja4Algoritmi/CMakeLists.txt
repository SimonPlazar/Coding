cmake_minimum_required(VERSION 3.21)
project(Vaja4Algoritmi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(Vaja4Algoritmi Vaja4Algoritmi.cpp)
