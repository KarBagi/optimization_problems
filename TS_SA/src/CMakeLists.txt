cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        Graph.cpp
        Graph.h
        Menu.cpp
        Menu.h
        pch.cpp
        pch.h
        PEA_E2.cpp
        SimulatedAnnealing.cpp
        SimulatedAnnealing.h
        TabuSearch.cpp
        TabuSearch.h)
