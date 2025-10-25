//
// Created by hp on 28-08-2025.
//

#include "PatternDatabase.h"
PatternDatabase :: PatternDatabase(size_t size) : size(size) , numItems(0) ,database(size){}

PatternDatabase :: PatternDatabase(size_t size,uint8_t init_val) : size(size) , numItems(0) , database(size,init_val){}

bool PatternDatabase::setNumMoves(RubiksCube & rubiksCube, uint8_t numMoves) {
    return this->setNumMoves(this->getIndex(rubiksCube),numMoves);
}

bool PatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves) {
    uint8_t oldMoves = this->getNumMoves(ind);

    //    New item is getting added
    if(oldMoves == 0xF){
        ++this->numItems;
    }

    if(oldMoves > numMoves){
        this->database.set(ind, numMoves);
        return true;
    }
    return false;

}

uint8_t PatternDatabase :: getNumMoves(RubiksCube & rubiksCube) {
    return this->getNumMoves(this->getIndex(rubiksCube)) ;

}

uint8_t PatternDatabase :: getNumMoves(uint8_t index) {
    return this->database.get(index);
}

size_t PatternDatabase::getSize() const {
    return this->size;
}

size_t PatternDatabase::getNumItems() const {
    return this->numItems;
}

bool PatternDatabase::isFull() const {
    return this->numItems == this->size;
}

void PatternDatabase::toFile(const string &filePath) const {

    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);

    if(!writer.is_open())
        throw "Failed to open the file to write";

    writer.write(
            reinterpret_cast<const char*>(this->database.data()),
            this->database.storageSize()
            );

    writer.close();
}

bool PatternDatabase::fromFile(const string &filePath) {
    ifstream reader(filePath, ios::in | ios::ate);

    if(!reader.is_open())
        return false;

    size_t fileSize = reader.tellg();

    if(fileSize != this->database.storageSize()){
        reader.close();
        throw "Database corrupt! Failed to open Reader";
    }

    reader.seekg(0, ios::beg);
    reader.read(
            reinterpret_cast<char*> (this->database.data()),
            this->database.storageSize()
            );
    reader.close();
    this->numItems = this->size;
    return true;
}

vector<uint8_t> PatternDatabase::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset() {
    if(this->numItems != 0){
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}