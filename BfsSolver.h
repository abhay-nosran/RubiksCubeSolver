//
// Created by Abhay Nosran on 26-07-2025.
//

#include "RubiksCube.h"
#include <unordered_map>
template <typename T,typename H>
class BfsSolver {
    vector<RubiksCube::MOVE> moves ;
    unordered_map<T,bool,H> visited ;
    unordered_map<T,RubiksCube::MOVE,H> moveDone ;

    T bfs() {

        queue<T> q; // store states of rubikcsCube
        q.push(rubiksCube);
        moveDone[rubiksCube] = RubiksCube::MOVE(0);
        visited[rubiksCube] = 1 ;

        while (!q.empty()) {

            T node = q.front() ; q.pop() ;
            // node.print();

            if (node.isSolved()) return node;

            for (int i = 0 ; i < 18 ; i++) {
                // ith move
                auto move = RubiksCube::MOVE(i) ;
                node.move(move);
                if (!visited[node]) {
                    visited[node] = 1 ;
                    moveDone[node] = move ;
                    q.push(node);
                }
                node.invertMove(move) ;
            }
        }
        return  rubiksCube ;
    }

public :
    T rubiksCube;

    vector<RubiksCube::MOVE> solve() {
       T solvedConfig = bfs();
        if (solvedConfig.isSolved() == 0) {
            moves.clear();
            return {};
        }

        T currentConfig = solvedConfig;
        while (!(currentConfig == rubiksCube)) {
            auto move = moveDone[currentConfig] ;
            moves.push_back(move);
            currentConfig.invertMove(move);
        }
        rubiksCube = solvedConfig ;
        reverse(moves.begin(), moves.end());
        return moves;
    }

    BfsSolver(T & rubiksCube) {
        this->rubiksCube = rubiksCube;
    }
};