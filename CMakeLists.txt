cmake_minimum_required(VERSION 3.31)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(RubiksCubeSolver main.cpp
        Model/RubiksCube.cpp
        Model/Cubes/RubiksCube3dArray.cpp
        Model/Cubes/RubiksCubeBitsModel.cpp
        Solver/BfsSolver.h
        Solver/IDDFSSolver.h
        "Solver/ID Astar/IDAStar.h"
        "Database/Nibble Array/NibbleArray.h"
        "Database/Nibble Array/NibbleArray.cpp"
        Database/Pattern/PatternDatabase.cpp
        Database/Pattern/PatternDatabase.h
        Database/Corner/CornerPatternDatabase.cpp
        Database/Indexer/math.cpp
        Database/Indexer/math.h
        Database/Indexer/PermutationIndexer.h
        Database/Corner/CornerPatternDatabase.h
        "Db Maker/CornerDBMaker.cpp"
        "Db Maker/CornerDBMaker.h"
)
