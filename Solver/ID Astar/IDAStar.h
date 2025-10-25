//
// Created by Abhay Nosran on 01-08-2025.
//

#ifndef IDASTAR_H
#define IDASTAR_H
#include "../../Model/RubiksCube.h"
#include "../../Database/Corner/CornerPatternDatabase.h"

template<typename T, typename H>
class IDAStarSolver {
    CornerPatternDatabase cornerDB;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, bool, H> visited;
    unordered_map<T, RubiksCube::MOVE, H> moveDone;

    struct Node {
        T rubiksCube;
        int g;
        int h;

        Node(T r, int g, int h) {
            rubiksCube = r;
            this->g = g;
            this->h = h;
        }

        Node(const Node &a) {
            this->rubiksCube = a.rubiksCube;
            this->g = a.g;
            this->h = a.h;
        }
    };

    struct comp {
        bool operator()(pair<Node,int> &p1 , pair<Node,int> &p2) {
           int f1 = p1.first.g + p1.first.h;
           int f2 = p2.first.g + p2.first.h;

            if (f1 == f2) {
                return p1.first.h > p2.first.h;
            }else return f1 > f2 ;
        }
    };

    // bool comp(Node left , Node right) {
    //
    //     if (left.g + left.h < right.g + right.h) return true;
    //     return false;
    // }

    void reset() {
        moves.clear();
        visited.clear();
        moveDone.clear();
    }

    // pair<T, pair<int, bool> > AStar(int bound) {
    //     priority_queue<Node, vector<Node>, comp> pq;
    //
    //     Node n(rubiksCube, 0, cornerDB.getNumMoves(rubiksCube));
    //     pq.push(n);
    //     visited[rubiksCube] = true;
    //     int next_bound = 100;
    //
    //     while (!pq.empty()) {
    //         Node node = pq.top();
    //         pq.pop();
    //
    //         if (node.rubiksCube.isSolved()) {
    //             return {node.rubiksCube, {node.g, 1}};
    //         }
    //
    //         for (int i = 0; i < 18; i++) {
    //             Node child(node);
    //             auto move = RubiksCube::MOVE(i);
    //             child.rubiksCube.move(move);
    //
    //             child.h = cornerDB.getNumMoves(child.rubiksCube); // new heuristic value
    //             child.g = node.g + 1;
    //
    //             if (!visited[child.rubiksCube]) {
    //                 if ((child.h + child.g) <= bound) {
    //                     moveDone[child.rubiksCube] = move;
    //                     pq.push(child);
    //                     visited[child.rubiksCube] = true;
    //                 } else {
    //                     next_bound = min(next_bound, child.h + child.g);
    //                 }
    //             }
    //         }
    //     }
    //
    //     return {rubiksCube, {next_bound, 0}};
    // }


    pair<T,int> Astar(int bound) {
        Node start(rubiksCube,0,cornerDB.getNumMoves(rubiksCube)) ;
        priority_queue<pair<Node,int>,vector<pair<Node,int>>,comp> pq;

        pq.push({start, 0});

        int next_bound = 100; // max 100 depth

        while (!pq.empty()) {

            auto state = pq.top() ; pq.pop() ;
            Node node = state.first;
            int move = state.second;

            if (visited[node.rubiksCube]) continue;

            visited[node.rubiksCube] = true;
            moveDone[node.rubiksCube] = RubiksCube :: MOVE(move);

            if (node.rubiksCube.isSolved()) return make_pair(node.rubiksCube, bound);

            node.g++ ;
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);

                node.rubiksCube.move(curr_move);

                if (!visited[node.rubiksCube]) {

                    node.h = cornerDB.getNumMoves(node.rubiksCube);

                    if (node.h + node.g > bound) {
                        next_bound = min(next_bound, node.g + node.h);
                    }else {
                        pq.push({node, i});
                    }
                }

                node.rubiksCube.invertMove(curr_move);
            }

        }

        return make_pair(rubiksCube, next_bound);
    }

public:
    T rubiksCube;

    IDAStarSolver(T &rubiksCube , string fileName){
        this->rubiksCube = rubiksCube;
        cornerDB.fromFile(fileName) ;
    }

    vector<RubiksCube::MOVE> solve() {
        int bound = 1 ;
        auto it = Astar(bound);
        while (it.second != bound) {
            reset();
            bound = it.second ;
            it = Astar(bound);
        }

        T solvedRubiksCube = it.first;
        T curRubiksCube = solvedRubiksCube;
        while (!(curRubiksCube == rubiksCube)) {
            auto move = moveDone[curRubiksCube];
            moves.push_back(move);
            curRubiksCube.invertMove(move);
        }

        rubiksCube = solvedRubiksCube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};
#endif //IDASTAR_H
