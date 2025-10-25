//
// Created by Abhay Nosran on 31-07-2025.
//
#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H


#include "../Model/RubiksCube.h"
#include "DfsSolver.h"
template<typename T>

class IDDfsSolver {
    int maxDepth ;
    vector<RubiksCube :: MOVE> moves ;
public:

    T rubiksCube ;
    IDDfsSolver(const T & rubiksCube , int maxDepth = 20) {

        this->rubiksCube = rubiksCube ;
        this->maxDepth = maxDepth ;
    }

    vector<RubiksCube :: MOVE> solve() {

        for (int i = 1 ; i <= maxDepth ; i++) {

            DfsSolver<T> dfsSolver(rubiksCube , i) ;
            moves = dfsSolver.solve();

            if (dfsSolver.rubiksCube.isSolved()) {
                rubiksCube = dfsSolver.rubiksCube ;
                break ;
            }
        }
        return moves ;
    }
};


#endif // IDDFSSOLVER_H
