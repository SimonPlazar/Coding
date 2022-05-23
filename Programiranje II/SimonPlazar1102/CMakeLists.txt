cmake_minimum_required(VERSION 3.21)
project(SimonPlazar1102)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimonPlazar1102 main.cpp Address.h Address.cpp Date.h Date.cpp Student.h Student.cpp UnparseableDateException.h UnparseableDateException.cpp Log.cpp Log.h InvalidFile.cpp InvalidFile.h)
