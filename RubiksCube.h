//
// Created by Abhay Nosran on 07-07-2025.
//

#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H


#include  <bits/stdc++.h>
using namespace std ;

class RubiksCube {

public :
    virtual ~RubiksCube() = default;

    enum class FACE{
        UP,
        FRONT,
        LEFT,
        RIGHT,
        BACK,
        DOWN
    };

    enum class COLOR {
        WHITE,
        RED,
        GREEN,
        BLUE,
        ORANGE,
        YELLOW
    };

    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    static string getMove(MOVE move);

    static char getColorInitials(COLOR c) ;

    void print() ;

   vector<MOVE> randomShuffle(int times);

    virtual bool isSolved() = 0 ;

    // performs move on the rubiks cube
    RubiksCube& move(MOVE m);
    RubiksCube& invertMove(MOVE m);

    virtual COLOR getColor(FACE f , int row , int column) const = 0 ;

    // 18 Rotational Moves
    // F,F',F2,
    // U,U',U2
    // L,L',L2
    // D,D',D2
    // R,R',R2
    // B,B',B2

    virtual  RubiksCube &f() = 0 ;
    virtual  RubiksCube &fPrime() = 0 ;
    virtual  RubiksCube &f2() = 0 ;

    virtual  RubiksCube &u() = 0 ;
    virtual  RubiksCube &uPrime() = 0 ;
    virtual  RubiksCube &u2() = 0 ;

    virtual RubiksCube &l() = 0 ;
    virtual  RubiksCube &lPrime() = 0 ;
    virtual RubiksCube &l2() = 0 ;

    virtual  RubiksCube &d() = 0 ;
    virtual  RubiksCube &dPrime() = 0 ;
    virtual RubiksCube &d2() = 0 ;

    virtual  RubiksCube &r() = 0 ;
    virtual  RubiksCube &rPrime() = 0 ;
    virtual  RubiksCube &r2() = 0 ;

    virtual  RubiksCube &b() = 0 ;
    virtual RubiksCube &bPrime() = 0 ;
    virtual  RubiksCube &b2() = 0 ;

    virtual RubiksCube& update(FACE ,int, int  , COLOR ) = 0 ;
    // friend  bool operator==(RubiksCube & a , RubiksCube & b) ; not implemented as a friend

    // bool operator==(RubiksCube & other ) const ;

    // virtual RubiksCube & operator=(const RubiksCube & other) = 0 ;
};



#endif //RUBIKSCUBE_H
