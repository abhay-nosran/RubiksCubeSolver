//
// Created by Abhay Nosran on 08-07-2025.
//

#include "RubiksCube.h"

class  RubiksCube3dArray : public  RubiksCube{
    // 6 face , 3 row , 3 col each has its own color
    // 0 - up
    // 1 - front
    // 2 - left
    // 3 - right
    // 4 - back
    // 5 - bottom

    char sticker[6][3][3] ; // 0 based indexing
    void rotateFace(int index) {

        char temp[3][3] ;
        for (int i = 0 ; i < 3 ; i++) {
            for (int j = 0 ; j < 3 ; j++) {
                temp[i][j] = sticker[index][i][j] ;
            }
        }

        // column 0,2 rotate
        for (int i = 0 ; i < 3 ; i++) sticker[index][0][2-i] = temp[i][0] ;
        for (int i = 0 ; i < 3 ; i++) sticker[index][2][2-i] = temp[i][2] ;

        //row 0,3 rotate
        for (int i = 0 ; i < 3 ; i++) sticker[index][i][2] = temp[0][i] ;
        for (int i = 0 ; i < 3 ; i++) sticker[index][i][0] = temp[2][i] ;
    }

public :

    RubiksCube3dArray() {

        for (int i = 0 ; i < 6 ; i++) {
            for (int j = 0 ; j < 3 ; j++) {
                for (int k = 0 ; k < 3 ; k++) {
                    sticker[i][j][k] = getColorInitials(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE f , const int row , const int column) override {
    switch (char c = sticker[static_cast<int>(f)][row][column]) {
        case 'R': return COLOR::RED;
        case 'B': return COLOR::BLUE;
        case 'G': return COLOR::GREEN;
        case 'Y': return COLOR::YELLOW;
        case 'W': return COLOR::WHITE;
        case 'O': return COLOR::ORANGE;
        default:return COLOR::WHITE ;
    }
}

    bool isSolved() override{

            for (int i = 0 ; i < 6 ; i++) {
                for (int j = 0 ; j < 3 ; j++) {
                    for (int k = 0 ; k < 3 ; k++) {

                        if (this->sticker[i][j][k] != getColorInitials(COLOR(i))) {
                            return false ;
                        }
                    }
                }
            }

            return true ;
        }

    RubiksCube &f() override {
        rotateFace(1);

        char preserve[3] ;

        // preserving face 2 2th col elements
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[2][i][2];

        //update face 2 2th column
        for (int i = 0 ; i < 3 ; i++) sticker[2][i][2] = sticker[5][0][i] ;

        //update face 5 oth row
        for (int i = 0 ; i < 3 ; i++) sticker[5][0][i] = sticker[3][2-i][0] ;

        //update face 3  oth col
        for (int i = 0 ; i < 3 ; i++) sticker[3][i][0] = sticker[0][2][i] ;

        //update face 0 2th row
        for (int i = 0 ; i < 3 ; i++) sticker[0][2][i] = preserve[2-i] ;

        return *this ;
    }

    RubiksCube &fPrime() override {
        this->f() ;
        this->f() ;
        this->f() ;
        return *this ;
    }

    RubiksCube &f2() override {
        this->f() ;
        this->f() ;
        return *this ;
    }

    RubiksCube &u() override {

        rotateFace(0);

        char preserve[3] ;
        // preserve face 1 oth row
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[1][0][i] ;

        // update face 1 oth row by face 3 0th row
        for (int i = 0 ; i < 3 ; i++) sticker[1][0][i] = sticker[3][0][i] ;

        // update face 3 0th row by face 4 oth row
        for (int i = 0 ; i < 3 ; i++) sticker[3][0][i] = sticker[4][0][i] ;

        //update face 4 0th row by face 2 0th row
        for (int i = 0 ; i < 3 ; i++) sticker[4][0][i] = sticker[2][0][i] ;

        // update face 2 0th row by face 1 0th row
        for (int i = 0 ; i < 3 ; i++) sticker[2][0][i] = preserve[i] ;

        return *this ;
    }

    RubiksCube &uPrime() override {
        this->u();
        this->u() ;
        this->u() ;
        return *this ;
    }

    RubiksCube &u2() override {
        this->u() ;
        this->u() ;
        return *this ;
    }

    RubiksCube &l() override {

        rotateFace(2) ;
        char preserve[3] ;

        // preserve face 0 0th column
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[0][i][0] ;

        //update face 0 0th column by face 1 0th column
        for (int i = 0 ; i < 3 ; i++) sticker[0][i][0] = sticker[1][i][0] ;

        // update face 1 0th column by face 5 0th column
        for (int i = 0 ; i < 3 ; i++) sticker[1][i][0] = sticker[5][i][0] ;

        // update face 5 0th column by face 4  2th column
        for (int i = 0 ; i < 3 ; i++) sticker[5][i][0] = sticker[4][i][2] ;

        //update face 4 2nd column by face 0 0th column
        for (int i = 0 ; i < 3 ; i++) sticker[4][i][2] = preserve[2-i] ;
        return *this ;
    };

    RubiksCube &lPrime() override {
        this->l() ;
        this->l() ;
        this->l() ;
        return *this ;
    }

    RubiksCube &l2() override {
        this->l() ;
        this->l() ;
        return *this ;
    }

    RubiksCube &r() override {

        rotateFace(3) ;

        char preserve[3] ;
        //preserve face 0 2th column
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[0][i][2] ;

        // update face 0 2nd column by face 1 2nd column
        for (int i = 0 ; i < 3 ; i++) sticker[0][i][2] = sticker[1][i][2] ;

        // update face 1 2nd column by face 5 2nd column
        for (int i = 0 ; i < 3 ; i++) sticker[1][i][2] = sticker[5][i][2] ;

        // update face 5 2nd column by face 4 0th column
        for (int i = 0 ; i < 3 ; i++) sticker[5][i][2] = sticker[4][2-i][0] ;

        // update face 4 0th  column by face 0 2nd column
        for (int i = 0 ; i < 3 ; i++) sticker[4][i][0] = preserve[2-i] ;

        return *this ;
    }

    RubiksCube &rPrime() override {
        this->r() ;
        this->r() ;
        this->r() ;
        return *this ;
    }

    RubiksCube &r2() override {
        this->r() ;
        this->r() ;
        return *this ;
    }

    RubiksCube &d() override {
        rotateFace(5) ;

        char preserve[3] ;

        // preserve face 1 2nd row
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[1][2][i] ;

        // update face 1 2nd row by face 2 2nd row
        for (int i = 0 ; i < 3 ; i++) sticker[1][2][i] = sticker[2][2][i] ;

        // update face 2 2nd row by face 4 2nd row
        for (int i = 0 ; i < 3 ; i++) sticker[2][2][i] = sticker[4][2][i] ;

        // update face 4 2nd row by face 3 2nd row
        for (int i = 0 ; i < 3 ; i++) sticker[4][2][i] = sticker[3][2][i] ;

        // update face 3 2nd row by face 1 2nd row
        for (int i = 0 ; i < 3 ; i++) sticker[3][2][i] = preserve[i] ;
        return  *this ;
    }

    RubiksCube &dPrime() override {
        this->d() ;
        this->d() ;
        this->d() ;
        return *this ;
    }

    RubiksCube &d2() override {
        this->d() ;
        this->d();
        return *this ;
    }

    RubiksCube &b() override {
        rotateFace(4) ;

        char preserve[3] ;

        // preserve face 0 0th row
        for (int i = 0 ; i < 3 ; i++) preserve[i] = sticker[0][0][i] ;

        // update face 0 0th row by face 3 2nd column
        for (int i = 0 ; i < 3 ; i++) sticker[0][0][i] = sticker[3][i][2] ;

        // update face 3 2nd column by face 5 2nd row
        for (int i = 0 ; i < 3 ; i ++) sticker[3][i][2] = sticker[5][2][2-i] ;

        // update face 5 2nd row by face 2 0th column
        for (int i = 0 ; i < 3 ; i++) sticker[5][2][i] = sticker[2][i][0] ;

        // update face 2 0th column by face 0 0th row
        for (int i = 0 ; i < 3 ; i++) sticker[2][i][0] = preserve[2-i] ;

        return *this ;
    }

    RubiksCube &bPrime() override {
        this->b() ;
        this->b() ;
        this->b() ;
        return *this ;
    }

    RubiksCube &b2() override {
        this->b() ;
        this->b() ;
        return *this ;
    }


};
