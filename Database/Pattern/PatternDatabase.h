//
// Created by Abhay Nosran on 28-08-2025.
//

#ifndef RUBIKSCUBESOLVER_PATTERNDATABASE_H
#define RUBIKSCUBESOLVER_PATTERNDATABASE_H
#include <cstdint>

#include "../Nibble Array/NibbleArray.h"
#include "../../Model/RubiksCube.h"


class PatternDatabase {

    NibbleArray database ;
    size_t size ;
    size_t numItems ;

    PatternDatabase() ;
public:
    PatternDatabase(size_t size) ;
    PatternDatabase(size_t size,uint8_t init_val) ;

    virtual  uint32_t getIndex(RubiksCube & rubiksCube) = 0 ;
    virtual  bool setNumMoves(RubiksCube & , uint8_t numMoves) ;
    virtual  bool setNumMoves(uint32_t index , uint8_t numMoves) ;

    virtual  uint8_t getNumMoves(RubiksCube &) ;
    virtual  uint8_t getNumMoves(uint8_t index) ;

    virtual size_t getSize() const;

    virtual size_t getNumItems() const;

    virtual bool isFull() const;

    virtual void toFile(const string &filePath) const;

    virtual bool fromFile(const string &filePath);

    virtual vector<uint8_t> inflate() const;

    virtual void reset();


};


#endif //RUBIKSCUBESOLVER_PATTERNDATABASE_H