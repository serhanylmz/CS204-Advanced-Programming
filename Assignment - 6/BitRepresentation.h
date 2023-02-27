//
// Written by Serhan Yilmaz
// Student Number: 00031275
//

#ifndef BITREPRESENTATION_H
#define BITREPRESENTATION_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename Type>

class BitRepresentation{
private:
    Type data;
public:
    explicit BitRepresentation(Type number);
    explicit BitRepresentation(const vector<bool> &boolVec);
    string getBinary(); // won't work
    string getHexadecimal();
    void setBit(unsigned int location);
    void unsetBit(unsigned int location);
    bool isBitSet(unsigned int location);
    Type getNumber();
};

#include "BitRepresentation.cpp"
#endif //BITREPRESENTATION_H