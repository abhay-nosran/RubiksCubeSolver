cmake_minimum_required(VERSION 3.31)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(RubiksCubeSolver main.cpp
        RubiksCube.cpp
        RubiksCube3dArray.cpp
        RubiksCubeBitsModel.cpp
        BfsSolver.h
)
