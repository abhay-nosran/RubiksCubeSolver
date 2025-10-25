//
// Created by Abhay Nosran on 12-07-2025.
//

#include "../RubiksCube.h"

class RubiksCubeBitsModel : public RubiksCube {
    int arr[3][3] = {{0,1,2},{7,8,3},{6,5,4}} ;
    void rotateFace(const int index) {

        // rotate index face

        // 0 1 2   6 7 0
        // 7 - 3   5 - 1
        // 6 5 4   4 3 2

        uint64_t face = faces[index];
        face = (face >> 48) ;
        faces[index] = (faces[index] << 16)|(face) ;
    }

    uint64_t one_8 = (1<<8) - 1 ;
    void rotateSide(int s1 , int s1_1 , int s1_2 , int s1_3 , int s2 , int s2_1 , int s2_2 , int s2_3) {

        // to put s2 into s1
        uint64_t  c1 = (faces[s2] & (one_8 << (8*s2_1))) >> (8*s2_1) ;
        uint64_t  c2 = (faces[s2] & (one_8 << (8*s2_2))) >> (8*s2_2) ;
        uint64_t  c3 = (faces[s2] & (one_8 << (8*s2_3))) >> (8*s2_3) ;

        faces[s1] = (faces[s1] & ~(one_8 << (8*s1_1))) | (c1 << (8*s1_1)) ;
        faces[s1] = (faces[s1] & ~(one_8 << (8*s1_2))) | (c2 << (8*s1_2)) ;
        faces[s1] = (faces[s1] & ~(one_8 << (8*s1_3))) | (c3 << (8*s1_3)) ;

    }

    void modifyCube(string s) {

        int size = s.length() ;
        if (size != 54) {
            cout << "Input Cube string is of length : " << size << endl ;
        }
        int index = 0 ;
        for (int face = 0 ; face < 6 ; face++) {
            for (int row = 0 ; row < 3 ; row++) {
                for (int col = 0 ; col < 3 ; col++) {
                        update(FACE(face),row,col,COLOR(s[index] - '0')) ;
                        index++ ;
                }
            }
        }
    }
public:
    uint64_t faces[6] ;
    RubiksCubeBitsModel() {

        for (int i = 0 ; i < 6 ; i++) {

            // set i th bit of every 8 bit set in a face
            faces[i] = 0ULL ;
            for (int j = 0 ; j < 8 ; j++) {
                faces[i] = faces[i] | (1ULL << (j*8+i)) ;
            }
        }
    }

    RubiksCubeBitsModel(string cubeInString) : RubiksCubeBitsModel()  {
        modifyCube(cubeInString) ;
    }

    string getCubeString() {
        string s = "";
        for (int face = 0 ; face < 6 ; face++) {
            for (int row = 0 ; row < 3 ; row++) {
                for (int col = 0 ; col < 3 ; col++) {
                    char c = '0' + int(getColor(FACE(face),row,col)) ;
                    s += c ;
                }
            }
        }
        return s ;
    }

    COLOR getColor(FACE f , int row , int col) const override{

        const int start = 8*(arr[row][col]) ;
        if (start == 64) return RubiksCube :: COLOR(int(f));
        const int end = start + 8 ;
        uint64_t bits = faces[static_cast<int>(f)] ;
        for (int i = start ; i < end ; i++) {

            // check ith bit set or not

            if ((1ULL<<i)&bits) {
                // ith bit is set
                // color i - start
                int color = i - start ; // colorth bit is set
                return static_cast<RubiksCube::COLOR>(color) ;
            }
        }
        return static_cast<RubiksCube::COLOR>(0) ; // default
    }

    RubiksCube& update(FACE f, int row, int col, COLOR c) override {
        uint64_t bits = 1ULL << (int(c)) ;

        faces[int(f)] = (faces[int(f)] & ~(one_8 << (8*arr[row][col]))) | (bits << (8*arr[row][col])) ;
        return *this ;
    };

    bool isSolved() override {

        for (int face = 0 ; face < 6 ; face++) {
            // all face bit set of each face

            for (int i = 0 ; i < 8 ; i++) {

                if (!(1<<(face + 8*i) & faces[face])) {
                    return false ;
                }
            }
        }
        return true ;
    };

    RubiksCube& f() override {

        rotateFace(1) ;
        uint64_t  c1 = (faces[0] & (one_8 << (8*4))) >> (8*4) ;
        uint64_t  c2 = (faces[0] & (one_8 << (8*5))) >> (8*5) ;
        uint64_t  c3 = (faces[0] & (one_8 << (8*6))) >> (8*6) ;

        rotateSide(0,4,5,6,2,2,3,4);
        rotateSide(2,2,3,4,5,0,1,2);
        rotateSide(5,0,1,2,3,6,7,0);

        faces[3] = (faces[3] & ~(one_8 << (8*0))) | (c3 << (8*0)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*7))) | (c2 << (8*7)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*6))) | (c1 << (8*6)) ;

        return *this ;
    };
    RubiksCube& f2() override {
        this->f() ;
        this->f() ;
        return *this ;
    }
    RubiksCube& fPrime() override {
        this->f() ;
        this->f() ;
        this->f() ;
        return *this ;
    }

    RubiksCube& b() override {
        rotateFace(4);

        uint64_t  c1 = (faces[0] & (one_8 << (8*0))) >> (8*0) ;
        uint64_t  c2 = (faces[0] & (one_8 << (8*1))) >> (8*1) ;
        uint64_t  c3 = (faces[0] & (one_8 << (8*2))) >> (8*2) ;

        rotateSide(0,0,1,2,3,2,3,4);
        rotateSide(3,2,3,4,5,4,5,6);
        rotateSide(5,4,5,6,2,6,7,0);

        // 6 7 0 <- 0 1 2
        faces[2] = (faces[2] & ~(one_8 << (8*6))) | (c1 << (8*6)) ;
        faces[2] = (faces[2] & ~(one_8 << (8*7))) | (c2 << (8*7)) ;
        faces[2] = (faces[2] & ~(one_8 << (8*0))) | (c3 << (8*0)) ;

        return *this ;

    }
    RubiksCube&b2() override {
        this->b() ;
        this->b() ;
        return *this ;
    };
    RubiksCube& bPrime() override {
        this->b() ;
        this->b() ;
        this->b() ;
        return *this ;
    }

    RubiksCube& l()override {

        rotateFace(2) ;

        uint64_t  c1 = (faces[0] & (one_8 << (8*0))) >> (8*0) ;
        uint64_t  c2 = (faces[0] & (one_8 << (8*7))) >> (8*7) ;
        uint64_t  c3 = (faces[0] & (one_8 << (8*6))) >> (8*6) ;

        rotateSide(0,0,7,6,4,4,3,2);
        rotateSide(4,2,3,4,5,6,7,0);
        rotateSide(5,6,7,0,1,6,7,0);

        // 1 (6,7,0) <-- 0(6,7,0)

        faces[1] = (faces[1] & ~(one_8 << (8*6))) | (c3 << (8*6)) ;
        faces[1] = (faces[1] & ~(one_8 << (8*7))) | (c2 << (8*7)) ;
        faces[1] = (faces[1] & ~(one_8 << (8*0))) | (c1 << (8*0)) ;

        return *this ;
    }
    RubiksCube& l2() override {
        this->l() ;
        this->l() ;
        return *this ;
    }
    RubiksCube& lPrime() override {
        this->l();
        this->l() ;
        this->l() ;
        return *this ;
    }

    RubiksCube& r() override {
        rotateFace(3) ;

        uint64_t  c1 = (faces[0] & (one_8 << (8*4))) >> (8*4) ;
        uint64_t  c2 = (faces[0] & (one_8 << (8*3))) >> (8*3) ;
        uint64_t  c3 = (faces[0] & (one_8 << (8*2))) >> (8*2) ;

        rotateSide(0,4,3,2,1,4,3,2) ;
        rotateSide(1,2,3,4,5,2,3,4) ;
        rotateSide(5,2,3,4,4,6,7,0);

        // 4 (0,7,6) <-- 0 (4,3,2)
        faces[4] = (faces[4] & ~(one_8 << (8*0))) | (c1 << (8*0)) ;
        faces[4] = (faces[4] & ~(one_8 << (8*7))) | (c2 << (8*7)) ;
        faces[4] = (faces[4] & ~(one_8 << (8*6))) | (c3 << (8*6)) ;

        return *this ;

    }
    RubiksCube& r2() override {
        this->r() ;
        this->r() ;
        return *this ;
    }
    RubiksCube& rPrime() override {
        this->r() ;
        this->r() ;
        this->r() ;
        return *this ;
    }

    RubiksCube& u() override {
        rotateFace(0) ;

        uint64_t  c1 = (faces[4] & (one_8 << (8*2))) >> (8*2) ;
        uint64_t  c2 = (faces[4] & (one_8 << (8*1))) >> (8*1) ;
        uint64_t  c3 = (faces[4] & (one_8 << (8*0))) >> (8*0) ;

        rotateSide(4,2,1,0,2,2,1,0);
        rotateSide(2,0,1,2,1,0,1,2);
        rotateSide(1,0,1,2,3,0,1,2);

        //3 (2,1,0)  <-- 4 (2 , 1 , 0)
        faces[3] = (faces[3] & ~(one_8 << (8*2))) | (c1 << (8*2)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*1))) | (c2 << (8*1)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*0))) | (c3 << (8*0)) ;

        return *this ;
    }
    RubiksCube& u2() override {
        this->u() ;
        this->u() ;
        return *this ;
    }
    RubiksCube& uPrime() override {
        this->u();
        this->u();
        this->u();
        return *this ;
    }

    RubiksCube& d() override {

        rotateFace(5) ;
        uint64_t  c1 = (faces[1] & (one_8 << (8*6))) >> (8*6) ;
        uint64_t  c2 = (faces[1] & (one_8 << (8*5))) >> (8*5) ;
        uint64_t  c3 = (faces[1] & (one_8 << (8*4))) >> (8*4) ;

        rotateSide(1,6,5,4,2,6,5,4) ;
        rotateSide(2,4,5,6,4,4,5,6) ;
        rotateSide(4,4,5,6,3,4,5,6) ;

        // 3 (4,5,6) <-- 1 (4,5,6)
        faces[3] = (faces[3] & ~(one_8 << (8*4))) | (c3 << (8*4)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*5))) | (c2 << (8*5)) ;
        faces[3] = (faces[3] & ~(one_8 << (8*6))) | (c1 << (8*6)) ;

        return *this ;
    }
    RubiksCube& d2() override {
        this->d() ;
        this->d() ;

        return *this ;
    }
    RubiksCube& dPrime() override {
        this->d() ;
        this->d() ;
        this->d() ;
        return *this ;
    }


    RubiksCubeBitsModel& operator=(const RubiksCubeBitsModel & other) {
        if (this == &other) return *this ;
        for (int i = 0 ; i < 6 ; i++) {
            faces[i] = other.faces[i] ;
        }

        return *this ;
    }

    bool operator==(const RubiksCubeBitsModel & other) const {

        for (int i = 0 ; i < 6 ; i++) {
            if (faces[i] != other.faces[i]) {
                return false;
            }
        }
        return true;
    }
};

class RubiksCubeBitsModelHash {

public:
    size_t operator()(const RubiksCubeBitsModel & r) const {

        string s ;

        for (int i = 0 ; i < 6 ; i++) {
            for (int j = 0 ; j < 3 ; j++) {
                for (int k = 0 ; k < 3 ; k++) {
                    s += RubiksCube::getColorInitials(r.getColor(RubiksCube::FACE(i),j,k)) ;
                }
            }
        }
        return hash<string>()(s) ;
    }
};