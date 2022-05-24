cmake_minimum_required(VERSION 3.21)
project(SimonPlazar1101)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimonPlazar1101 main.cpp Address.cpp Address.h Date.cpp Date.h Student.cpp Student.h UnparseableDateException.cpp UnparseableDateException.h WrongDateException.cpp WrongDateException.h)
