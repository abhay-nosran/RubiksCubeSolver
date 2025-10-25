//
// Created by hp on 28-08-2025.
//

#ifndef RUBIKSCUBESOLVER_CORNERDBMAKER_H
#define RUBIKSCUBESOLVER_CORNERDBMAKER_H
#include "../Database/Corner/CornerPatternDatabase.h"

class CornerDBMaker {
private:
    string fileName;
    CornerPatternDatabase cornerDB;

public:
    CornerDBMaker(string _fileName);
    CornerDBMaker(string _fileName, uint8_t init_val);

    bool bfsAndStore();
};


#endif //RUBIKSCUBESOLVER_CORNERDBMAKER_H