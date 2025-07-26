#include "RubiksCube3dArray.cpp"
#include "DfsSolver.h"
#include "RubiksCube.h"
#include "BfsSolver.h"
using  namespace  std ;
int main() {
    RubiksCube3dArray model ;
    vector<RubiksCube::MOVE> moves = model.randomShuffle((7));

    for (auto move : moves) {
        cout << RubiksCube :: getMove(move) << ' ';
    }
    cout << '\n' ;

    // DfsSolver<RubiksCube3dArray> dfs(model);
    // vector<RubiksCube::MOVE> m = dfs.solve();
    //
    // for (auto move : m) {
    //     cout << RubiksCube :: getMove(move) << ' ';
    // }cout << '\n' ;
    // model.print();

    BfsSolver<RubiksCube3dArray,RubiksCube3dArrayHash> bfs(model);
    vector<RubiksCube::MOVE> m2 = bfs.solve();
    for (auto move : m2) {
        cout << RubiksCube :: getMove(move) << ' ';
    }cout << '\n' ;
    // model.print();
    return 0;
}