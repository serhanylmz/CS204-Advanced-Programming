//
// Written by Serhan Yilmaz
// Student Number: 00031275
//
#include "BitRepresentation.h"
template<typename Type>
BitRepresentation<Type>::BitRepresentation(Type number) {
    data = number;
}

template <typename Type>
BitRepresentation<Type>::BitRepresentation(const vector<bool> &boolVec){
    data = 0; //first initiate the data as 0, since that's 0000...0000 regardless of how many bytes there are
    vector<bool> reversed = {}; //create a reversed vector from the initial boolVec.
    for(int i = boolVec.size()-1; i >= 0; i--){ //here's the reversal
        reversed.push_back(boolVec[i]);
    }
    //now, we have reversed this vector since we want to have (i < sizeof(Type)*8) && (i < reversed.size()) as the condition for the for loop)
    //I was looking if I could start from the largest index of the normal (non-reversed) vector, but then this creates the problem that
    // if i >= sizeof(Type)*8 then this would be a problem since the last bit would not have anywhere to go and be discarded.
    //here instead, the LSB is preserved and the MSB is discarded
    for (int i = 0; (i < sizeof(Type)*8) && (i < reversed.size()); i++){
        if (reversed[i]){
            data |= (1 << i);
        }
    }
}

template<typename Type>
string BitRepresentation<Type>::getBinary() {
    string binaryNumber = "";
    //very simple logic here, start from the MSB and mask every bit
    //if 1 then add 1 to the final string and if 0 then add zero, boom!
    for(int i = sizeof(Type)*8; i >= 0; i--){

        char finalBitChar;
        Type mask = (1 << i);
        if(data & mask){
            finalBitChar = '1';
        }
        else{
            finalBitChar = '0';
        }
        binaryNumber += finalBitChar;
    }
    binaryNumber = binaryNumber.substr(1);
    return binaryNumber;
}

template <typename Type>
string BitRepresentation<Type>::getHexadecimal(){
    string hexNumber = "";
    //quite similar logic here but only a bit different
    //every bit represents a binary number, i.e in the base 2
    //then, every 4 bits must represent a hex number, i.e in the base 2^4 = 16
    //so with that logic, parse the string with every four bits, convert that 4-bit part into a binary number
    //and then, whatever number you get will give you the corresponding hex digit here "0123456789ABCDEF"[finalBit]
    //and then, just add that to the final string
    unsigned int binary1111 = 15;
    for (int i = sizeof(Type)*2; i >= 0; i--){
        Type finalBit = data >> (i * 4);
        finalBit = finalBit & binary1111;
        char finalBitChar = "0123456789ABCDEF"[finalBit];
        hexNumber += finalBitChar;
    }
    hexNumber = hexNumber.substr(1);
    return hexNumber;
}

template<typename Type>
Type BitRepresentation<Type>::getNumber() {
    return data;
}

template<typename Type>
void BitRepresentation<Type>::setBit(unsigned int location){
    if(location >= sizeof(Type)*8){ //if the given location shows a non-existent index, then don't bother computing and just return
        return;
    }
    if(isBitSet(location)){//if the desired location already has a set bit, then return and don't bother changing.
        return;
    }
    Type mask; //create a mask first
    mask = (1<<location); //then, let mask be equal to 0000...0100...0000 where 1 is shifted left by 'location' indices
    data = data ^ mask; //afterwards, apply the XOR operator to set the given bit.
    //more explanation on how this works: suppose that the type is char and data is 0000 0000
    //if the function is called with the location = 5, here is our mask: 0010 0000
    //then, when the XOR operator is called, all the matching zeroes will remain 0, and all the 0-1 matches will be 1
    //as there is no other match -remember, we are checking if there are any 1-1 matches with the if(isSetBit(location))-
    //we end up only setting the bit we want to set.
}

template<typename Type>
bool BitRepresentation<Type>::isBitSet(unsigned int location) {
    //super simple logic, create a mask with a 1 in the location we wish to check
    //then, compare with the initial data with the mask using the & operator
    //this should isolate the bit at the location, if it's 1, then the number would be greater than 0, hence would be true
    //if it is 0, then the whole number will be zero which is false in bool
    if (location >= sizeof(Type)*8){
        return false;
    }
    Type mask = 1 << location;
    if(data & mask){
        return true;
    }
    else{
        return false;
    }

}

template<typename Type>
void BitRepresentation<Type>::unsetBit(unsigned int location) {
    if (location >= sizeof(Type)*8){ //if the index is not in the number, then just return and don't bother
        return;
    }
    Type mask; //create a mask first
    mask = ~(1 << location); //then, let the mask be equal to the inverse of what we have done in setBit()
    //in other words, shift '1' by 'location' indexes and take the inverse, so for example:
    //if type is char and location = 5, then mask is ~(0010 0000) which is 1101 1111

    data = data & mask; //finally, mask data with the & operator.
    //this operation is in fact the following: (p => q)' = (p` v  q)` = p & q' where p is data and q is mask
    //in other words, what happens is, say when data is 0000 0000 and mask is 1101 1111, the matching bit will be made 0
    //and the rest will remain whatever they were before (recall that p & 1 = 1 in logic)
    //therefore it unsets the bit. unlike the setBit, unsigning a bit twice will not give an error
    //as p & 0 = 0 is always true
}