//
// Created by Abhay Nosran on 17-07-2025.
//

#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#endif //DFSSOLVER_H

#include  "RubiksCube.h"

template <typename T>
class DfsSolver {
    int maxDepth ;
    vector<RubiksCube::MOVE> moves ;
    bool dfs(int depth) {
        // cout << "depth: " << depth << endl;
        // cout << rubiksCube.isSolved() << endl;
        if (rubiksCube.isSolved()) return true ;
        if (depth > maxDepth) return false ;
        for (int i = 0 ; i < 18 ; i++) {

            rubiksCube.move(RubiksCube::MOVE(i)) ;
            moves.push_back(RubiksCube::MOVE(i)) ;

            if (dfs(depth+1)) return true;

            moves.pop_back();
            rubiksCube.invertMove(static_cast<RubiksCube::MOVE>(i));
        }

        return false ;
    }
    public:
        T rubiksCube ;
        DfsSolver(T & r , int maxDepth = 8) {
            this->rubiksCube = r ;
            this->maxDepth = maxDepth ;
        } ;

        vector<RubiksCube::MOVE> solve() {
            dfs(0) ;
            return moves ;
        }
};