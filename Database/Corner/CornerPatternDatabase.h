//
// Created by hp on 28-08-2025.
//

#ifndef RUBIKSCUBESOLVER_CORNERPATTERNDATABASE_H
#define RUBIKSCUBESOLVER_CORNERPATTERNDATABASE_H
#include "../Pattern/PatternDatabase.h"
#include "../Indexer/PermutationIndexer.h"

class  CornerPatternDatabase : public  PatternDatabase {
    PermutationIndexer<8> permIndexer;
public:
    CornerPatternDatabase() ;
    CornerPatternDatabase(uint8_t init_val);

    uint32_t getIndex(RubiksCube & rubiksCube) ;
};

#endif //RUBIKSCUBESOLVER_CORNERPATTERNDATABASE_H