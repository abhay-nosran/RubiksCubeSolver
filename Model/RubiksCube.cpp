//
// Created by Abhay Nosran on 07-07-2025.
//

#include "RubiksCube.h"

char RubiksCube::getColorInitials(COLOR c) {

    switch (c) {
            case COLOR::RED: return 'R';
            case COLOR::BLUE: return 'B';
            case COLOR::GREEN: return 'G';
            case COLOR::YELLOW: return 'Y';
            case COLOR::WHITE: return 'W';
            case COLOR::ORANGE: return 'O';
    }
    return '?' ;
}

string RubiksCube::getMove(const MOVE move) {
    switch (move) {
        case MOVE::B : return "B" ;
        case MOVE::BPRIME : return "B'";
        case MOVE::B2 : return "B2" ;

        case MOVE::D : return "D" ;
        case MOVE::DPRIME : return "D'";
        case MOVE::D2 : return "D2" ;

        case  MOVE::F : return "F" ;
        case MOVE::F2 : return "F2" ;
        case MOVE::FPRIME : return "F'" ;

        case MOVE::L : return "L" ;
        case MOVE::L2 : return "L2" ;
        case MOVE::LPRIME : return "L'" ;

        case MOVE::R : return "R" ;
        case MOVE::RPRIME : return "R'" ;
        case MOVE::R2 : return "R2" ;

        case MOVE::U : return "U" ;
        case MOVE::UPRIME : return "U'" ;
        case MOVE::U2 : return "U2" ;

        default: return "?" ;
    }
}

RubiksCube& RubiksCube :: move(const MOVE m) {

    switch (m) {
        case MOVE::B : return this->b() ;
        case MOVE::B2 : return this->b2() ;
        case MOVE::BPRIME : return this->bPrime() ;

        case MOVE::D : return this->d() ;
            case MOVE::DPRIME : return this->dPrime() ;
            case MOVE::D2 : return this->d2() ;

            case MOVE::F : return this->f() ;
            case MOVE::F2 : return this->f2() ;
            case MOVE::FPRIME : return this->fPrime() ;

            case MOVE::L : return this->l() ;
            case MOVE::L2 : return this->l2() ;
            case MOVE::LPRIME : return this->lPrime() ;

            case MOVE::R : return this->r() ;
            case MOVE::RPRIME : return this->rPrime() ;
            case MOVE::R2 : return this->r2() ;

            case MOVE::U : return this->u() ;
            case MOVE::UPRIME : return this->uPrime() ;
            default: return this->u2();
    }
}

RubiksCube &RubiksCube::invertMove(MOVE m) {
    switch (m) {
        case MOVE::L:
            return this->lPrime();
        case MOVE::LPRIME:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->rPrime();
        case MOVE::RPRIME:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->uPrime();
        case MOVE::UPRIME:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->dPrime();
        case MOVE::DPRIME:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->fPrime();
        case MOVE::FPRIME:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->bPrime();
        case MOVE::BPRIME:
            return this->b();
        case MOVE::B2:
            return this->b2();
    }
    return this->b2();
}

vector<RubiksCube::MOVE> RubiksCube :: randomShuffle(int times) {

    vector<MOVE> moves;
    for (int i = 0 ; i < times ; i++) {
        int random = rand()%18 ;
        moves.push_back(static_cast<MOVE>(random));
        this->move(static_cast<MOVE>(random));
    }

    return  moves;
}

void RubiksCube::print() {

    cout << "RUBIKS CUBE" << '\n' ;

    for (int i = 0 ; i < 3 ; i++) {

        for (int j = 0 ; j < 7 ; j++) cout << ' ' ;

        for (int k = 0 ; k < 3 ; k++) {

            // Face UP (i,k)
            cout << getColorInitials(this->getColor(FACE::UP,i,k)) << ' ' ;
        }
        cout << '\n' ;
    }
    cout << '\n' ;

    for (int i = 0 ; i < 3 ; i++) {
        // Face LEFT (i,j)
        for (int j = 0 ; j < 3 ; j++) {
            cout << getColorInitials(this->getColor(FACE::LEFT,i,j)) << ' ' ;
        }
        cout << ' ';

        // Face FRONT (i,j)
        for (int j = 0 ; j < 3 ; j++) {
            cout << getColorInitials(this->getColor(FACE::FRONT,i,j)) << ' ' ;
        }
        cout << ' ' ;
        // Face RIGHT (i,j)
        for (int j = 0 ; j < 3 ; j++) {
            cout << getColorInitials(this->getColor(FACE::RIGHT,i,j)) << ' ' ;
        }
        cout << ' ' ;

        // Face BACK (i,j)
        for (int j = 0 ; j < 3 ; j++) {
            cout << getColorInitials(this->getColor(FACE::BACK,i,j)) << ' ' ;
        }
        cout << '\n' ;
    }

    cout << '\n' ;

    // FACE DOWN (i,j)
    for (int i = 0 ; i < 3 ; i++) {

        for (int j = 0 ; j < 7 ; j++) cout << ' ' ;
        for (int j = 0 ; j < 3 ; j++) {
            cout << getColorInitials(this->getColor(FACE::DOWN,i,j)) << ' ' ;
        }
        cout << "\n" ;
    }
    cout << '\n' ;
}

string RubiksCube::getColorStrip(uint8_t index) {
    string color = "";
    switch (index) {

        //FUL
        case 0 :
            color += getColorInitials(getColor(FACE::FRONT,0,0));
            color += getColorInitials(getColor(FACE::UP,2,0));
            color += getColorInitials(getColor(FACE::LEFT,0,2));
            break;

        //FUR
        case 1:
            color += getColorInitials(getColor(FACE::FRONT,0,2));
            color += getColorInitials(getColor(FACE::UP,2,2));
            color += getColorInitials(getColor(FACE::RIGHT,0,0));
            break;

        //FDL
        case 2 :
            color += getColorInitials(getColor(FACE::FRONT,2,0));
            color += getColorInitials(getColor(FACE::DOWN,0,0));
            color += getColorInitials(getColor(FACE::LEFT,2,2));
            break;

        //FDR
        case 3 :
            color += getColorInitials(getColor(FACE::FRONT,2,2));
            color += getColorInitials(getColor(FACE::DOWN,0,2));
            color += getColorInitials(getColor(FACE::RIGHT,2,0));
            break;

        //BUL
        case 4 :
            color += getColorInitials(getColor(FACE::BACK,0,2));
            color += getColorInitials(getColor(FACE::UP,0,0));
            color += getColorInitials(getColor(FACE::LEFT,0,0));
            break;
        //BUR
        case 5 :
            color += getColorInitials(getColor(FACE::BACK,0,0));
            color += getColorInitials(getColor(FACE::UP,0,2));
            color += getColorInitials(getColor(FACE::RIGHT,0,2));
            break;
        //BDL
        case 6 :
            color += getColorInitials(getColor(FACE::BACK,2,2));
            color += getColorInitials(getColor(FACE::DOWN,2,0));
            color += getColorInitials(getColor(FACE::LEFT,0,2));
            break ;

            //BDR
        case 7 :
            color += getColorInitials(getColor(FACE::BACK,2,0));
            color += getColorInitials(getColor(FACE::DOWN,2,2));
            color += getColorInitials(getColor(FACE::RIGHT,2,2));
        default:
            break;
    }
    return color ;
}


uint8_t RubiksCube::getCornerIndex(uint8_t index) {
    string s = getColorStrip(index) ;

    uint8_t ans = 0 ;

    for (auto it : s) {
        if (it != 'R' && it != 'O') continue;
        if (it == 'O') ans = ans | (1<<2)  ;
    }
    for (auto it : s) {
        if (it != 'W' && it != 'Y') continue;
        if (it == 'Y') ans = ans | (1<<1)  ;
    }
    for (auto it : s) {
        if (it != 'B' && it != 'G') continue;
        if (it == 'B') ans = ans | (1<<0)  ;
    }

    return ans ;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t index) {
    // 0 1 2
    string corner = getColorStrip(index) ;
    string s = "" ;

    for (auto it : corner) {
        if (it != 'W' && it != 'Y') continue;
        s+=it ;
    }

    if (s[0] == corner[0]) return 0 ;
    else if (s[0]==corner[1]) return 1 ;
    else return 2 ;
}

// bool RubiksCube::operator==(RubiksCube &other) const {
//     for (int face = 0 ; face < 7 ; face++) {
//         for (int row = 0 ; row < 3 ; row++) {
//             for (int col = 0 ; col < 3 ; col++) {
//                 if (this->getColor(static_cast<RubiksCube::FACE>(face),row,col) != other.getColor(RubiksCube::FACE(face),row,col)) {
//                     return false;
//                 }
//             }
//         }
//     }
//
//     return true;
// }

// RubiksCube & RubiksCube :: operator=(const RubiksCube & other) {
//
//     if (this == &other) return *this ;
//     for (int face = 0 ; face < 6 ; face++) {
//         for (int row = 0 ; row < 3 ; row++) {
//             for (int col = 0 ; col < 3 ; col++) {
//                 this->update(static_cast<RubiksCube::FACE>(face) , row , col , other.getColor( static_cast<FACE>(face) , row , col));
//             }
//         }
//     }
//
//     return *this ;
// }
