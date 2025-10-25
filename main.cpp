#include "Db Maker/CornerDBMaker.h"
#include "Solver/ID Astar/IDAStar.h"
#include "Model/Cubes/RubiksCube3dArray.cpp"
#include "Model/Cubes/RubiksCubeBitsModel.cpp"
#include "Model/RubiksCube.h"
#include "Solver/IDDFSSolver.h"
using  namespace  std ;
int main() {
    // RubiksCubeBitsModel model ;
    // // model.print() ;
    //
    // // model.b();
    // // model.print();
    // // model.bPrime();
    // // model.u();
    // // model.print() ;
    // // model.uPrime();
    // // model.d();
    // // model.print() ;
    // vector<RubiksCube::MOVE> moves = model.randomShuffle((8));
    //
    //
    // for (auto move : moves) {
    //     cout << RubiksCube :: getMove(move) << ' ';
    // }
    // cout << '\n' ;
    //
    // // IDDfsSolver<RubiksCubeBitsModel> solver(model) ;
    // IDAStarSolver<RubiksCubeBitsModel,RubiksCubeBitsModelHash> solver(model) ;
    // vector<RubiksCube::MOVE> m = solver.solve();
    //
    // for (auto move : m) {
    //     cout << RubiksCube :: getMove(move) << ' ';
    // }cout << '\n' ;
    // model.print();
    // solver.rubiksCube.print();
    //
    //
    //
    // // DfsSolver<RubiksCube3dArray> dfs(model);
    // // vector<RubiksCube::MOVE> m = dfs.solve();
    // //
    // // for (auto move : m) {
    // //     cout << RubiksCube :: getMove(move) << ' ';
    // // }cout << '\n' ;
    // // model.print();
    //
    // // BfsSolver<RubiksCube3dArray,RubiksCube3dArrayHash> bfs(model);
    // // // vector<RubiksCube::MOVE> m2 = bfs.solve();
    // // for (auto move : m2) {
    // //     cout << RubiksCube :: getMove(move) << ' ';
    // // }cout << '\n' ;
    // // // model.print();
    // return 0;

    // RubiksCubeBitsModel cube;
    // cube.print();
    //
    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(5);
    // for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();
    //
    // IDAStarSolver<RubiksCubeBitsModel, RubiksCubeBitsModelHash> idAstarSolver(cube);
    // vector<RubiksCube::MOVE> solve_moves = idAstarSolver.solve();
    // for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // idAstarSolver.rubiksCube.print();

    // string s = "010502304131114210225023124313235034404541243525450351" ;
    // RubiksCubeBitsModel cube(s) ;

    string fileName = "C:\\Users\\hp\\CLionProjects\\RubiksCubeSolver\\depth2.txt";
    // CornerDBMaker c(fileName,16) ;
    // c.bfsAndStore() ;
    RubiksCubeBitsModel cube ;
    auto it  = cube.randomShuffle(6) ;
    for (auto move: it) cout << RubiksCube::getMove(move) << " ";
    cube.print() ;
    IDAStarSolver<RubiksCubeBitsModel,RubiksCubeBitsModelHash> solver(cube,fileName) ;
    vector<RubiksCube::MOVE> steps = solver.solve() ;
    for (auto move: steps) cout << RubiksCube::getMove(move) << " ";

}