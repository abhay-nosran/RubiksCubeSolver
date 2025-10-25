//
// Created by hp on 28-08-2025.
//

#include "CornerDBMaker.h"
#include "../Model/Cubes/RubiksCubeBitsModel.cpp"
CornerDBMaker::CornerDBMaker(string _fileName) {
    fileName = _fileName;
}

CornerDBMaker::CornerDBMaker(string _fileName, uint8_t init_val) {
    fileName = _fileName;
    cornerDB = CornerPatternDatabase(init_val);
}


bool CornerDBMaker::bfsAndStore() {
    RubiksCubeBitsModel cube;
    queue<RubiksCubeBitsModel> q;
    q.push(cube);
    cornerDB.setNumMoves(cube, 0);
    int curr_depth = 0;
    while (!q.empty()) {
        int n = q.size();
        curr_depth++;
        if (curr_depth == 12) break;
        for (int counter = 0; counter < n; counter++) {
            RubiksCubeBitsModel node = q.front();
            q.pop();
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                if ((int) cornerDB.getNumMoves(node) > curr_depth) {
                    cornerDB.setNumMoves(node, curr_depth);
                    q.push(node);
                }
                node.invertMove(curr_move);
            }
        }
    }

    cornerDB.toFile(fileName);
    return true;
}